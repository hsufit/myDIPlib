#include<stdio.h>
#include<stdlib.h>
#include"bmpRW.h"

void bmpRFunc(char *fileN,struct bmpD **pointer)
{
	int i,j;

	FILE* f;
	struct bmpD *data;

	f=fopen(fileN,"rb");

	if( f == NULL)
		printf("can not open the file : \"%s\"",fileN);

	data=(struct bmpD*)malloc(sizeof(struct bmpD));

    fread(data,1,2,f);
    fread(&(data->sizeT),1,52,f);

	if(data->UsedColors!=0)
	{
		data->Colors = malloc(sizeof(char)*4*data->UsedColors);
		fseek(f, 54, SEEK_SET);
		fread(data->Colors,sizeof(char),data->UsedColors*4,f);

		data->C.RY=malloc(sizeof(char)*data->Width*4*abs(data->Height));
		fseek(f, data->offsetRGB, SEEK_SET);
		for(i=0;i<abs(data->Height);i++)
		{
			for(j=0;j<abs(data->Width);j++)
			{
				fread(&(data->C.RY[i*data->Width+j]),1,1,f);
			}
//skip zero padding
		fseek(f, (4-data->Width*3%4)%4, SEEK_CUR);
		}
	}
	else
	{
		data->C.RY=malloc(sizeof(char)*data->Width*abs(data->Height));
		data->C.GU=malloc(sizeof(char)*data->Width*abs(data->Height));
		data->C.BV=malloc(sizeof(char)*data->Width*abs(data->Height));
		if(data->BPP==32)//have alpha
			data->Alpha=malloc(sizeof(char)*data->Width*abs(data->Height));
		fseek(f, data->offsetRGB, SEEK_SET);
		for(i=0;i<abs(data->Height);i++)
		{
			for(j=0;j<abs(data->Width);j++)
			{
				fread(&(data->C.BV[i*data->Width+j]),1,1,f);
				fread(&(data->C.GU[i*data->Width+j]),1,1,f);
				fread(&(data->C.RY[i*data->Width+j]),1,1,f);
				if(data->BPP==32)//have alpha
					fread(&(data->Alpha[i*data->Width+j]),1,1,f);

			}
//skip zero padding
		if(data->BPP==32)
			fseek(f, (4-data->Width*4%4)%4, SEEK_CUR);
		else
			fseek(f, (4-data->Width*3%4)%4, SEEK_CUR);
		}
	}


	headerPrint(data);
	*pointer=data;
}


//dir is the bit map horizontal direction
void bmpWFunc(char *fileN, struct bmpD* data, bool dir)
{
	int i,j;
	char tmp=0;

	FILE *f;

    f=fopen(fileN,"wb");
	if( f == NULL)
		printf("can not open the file : \"%s\"\n",fileN);
	else
		printf("open the file : \"%s\" success!\n",fileN);

	if(data->UsedColors==0)
		data->sizeT = 54 + (data->Width+(4-data->Width%4)%4)*abs(data->Height)*data->BPP/8;
	else
		data->sizeT = 54 + data->UsedColors*4 + data->Width*abs(data->Height);

	data->offsetRGB = 54 + data->UsedColors*4;

	data->sizeD = (data->Width+(4-data->Width%4)%4)*abs(data->Height)*data->BPP/8;

	if(dir==0)
	    data->Height=abs(data->Height);
	else
	    data->Height=-abs(data->Height);

printf("\noutput at : %s\n",fileN);
headerPrint(data);


    fwrite(data,1,2,f);
    fwrite(&(data->sizeT),1,52,f);


	if(data->UsedColors!=0)
	{
		fwrite(data->Colors, 1, data->UsedColors*4, f);
	    for(i=0;i<abs(data->Height);i++)
		{
	        for(j=0;j<abs(data->Width);j++)
				fwrite(&(data->C.RY[i*data->Width+j]),1,1,f);

			for(j=0;j<(4-data->Width*3%4)%4;j++)
				fwrite(&tmp,1,1,f);
		}
	}
	else
	    for(i=0;i<abs(data->Height);i++)
		{
	        for(j=0;j<abs(data->Width);j++)
    	    {
				fwrite(&(data->C.BV[i*data->Width+j]),1,1,f);
				fwrite(&(data->C.GU[i*data->Width+j]),1,1,f);
		 		fwrite(&(data->C.RY[i*data->Width+j]),1,1,f);
				if(data->BPP==32)
			 		fwrite(&(data->Alpha[i*data->Width+j]),1,1,f);
			}
			if(data->BPP==32)
				for(j=0;j<(4-data->Width*4%4)%4;j++)
					fwrite(&tmp,1,1,f);
			else
				for(j=0;j<(4-data->Width*3%4)%4;j++)
					fwrite(&tmp,1,1,f);
		}
//unsigned char k=0x8c;
//fwrite(&k,1,1,f);

}



void headerPrint(struct bmpD* data)
{
	int i;

	printf("Image info :\n");
	printf("%c%c\n",data->ID[0],data->ID[1]);
	printf("File size : %d\n",data->sizeT);
	printf("BMP data offset : %d\n",data->offsetRGB);

	printf("BMP header size : %d\n",data->sizeInfo);
	printf("Width=%d  Height=%d\n",data->Width,data->Height);
	printf("number of color plans : %d\n",data->planes);
	printf("numbers of bit per pixel : %d\n",data->BPP);
	printf("compression method used : %d\n",data->compression);
	printf("raw RGB data size : %d\n",data->sizeD);
	printf("horizontal resolution : %d\n",data->Hresolution);
	printf("vertical resolution : %d\n",data->Vresolution);
	printf("numbers of color in color plane : %d\n",data->UsedColors);
	printf("Number of important colors : %d\n",data->ImportColors);

	if(data->UsedColors == 0)
		printf("no color plane data\n");
	else
	{
		printf("color palette data :\n");
		for(i=0;i<data->UsedColors/2;i++)
		{
			printf("R=%3u, G=%3u, B=%3u, A=%3u | ",data->Colors[i*8],data->Colors[i*8+1],data->Colors[i*8+2],data->Colors[i*8+3]);
			printf("R=%3u, G=%3u, B=%3u, A=%3u\n",data->Colors[i*8+4],data->Colors[i*8+5],data->Colors[i*8+6],data->Colors[i*8+7]);
		}
	}
}



void YUV420RFunc(char *fileN, struct charcontainer_3 *data, unsigned int Width, unsigned int Height, unsigned int fn)
{
	int i,j;
	char *U,*V;
	FILE *f;

	f=fopen(fileN,"rb");
	if( f == NULL)
		printf("can not open the file : \"%s\"\n",fileN);
	else
		printf("open the file : \"%s\" success!\n",fileN);

//printf("%10ld\n",ftell(f));

	fseek(f, fn*Width*Height*3/2, SEEK_SET);

//printf("%10ld, seek : %d, %d\n",ftell(f), fn,Width*Height*3/2);

	fread(data->RY,Width*Height,1,f);
	U = malloc(sizeof(unsigned char)*Width*Height/4);
	fread(U,Width*Height/4,1,f);
	V = malloc(sizeof(unsigned char)*Width*Height/4);
	fread(V,Width*Height/4,1,f);

	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
//printf("start:(%3d,%3d)=(%3d,%3d)\n",j,i,j/2,i/2);
			data->GU[i*Width+j] = U[i/2*(Width/2)+j/2];
			data->BV[i*Width+j] = V[i/2*(Width/2)+j/2];
//printf("end:(%3d,%3d)=(%3d,%3d)\n",j,i,j/2,i/2);
		}

	free(U);
	free(V);
	fclose(f);
}




