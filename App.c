#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include"./App.h"

void Scailing_RGB(struct bmpD* Img, int OWidth, int OHeight)
{
	unsigned char *temp;

	temp = (unsigned char*)malloc(sizeof(unsigned char)*OWidth*OHeight);
	Scailing(Img->C.RY, Img->Width, Img->Height, temp, OWidth, OHeight);
	free(Img->C.RY);
	Img->C.RY=temp;

	temp = (unsigned char*)malloc(sizeof(unsigned char)*OWidth*OHeight);
	Scailing(Img->C.GU, Img->Width, Img->Height, temp, OWidth, OHeight);
	free(Img->C.GU);
	Img->C.GU=temp;

	temp = (unsigned char*)malloc(sizeof(unsigned char)*OWidth*OHeight);
	Scailing(Img->C.BV, Img->Width, Img->Height, temp, OWidth, OHeight);
	free(Img->C.BV);
	Img->C.BV=temp;

	if(Img->BPP==32)
	{
		temp = (unsigned char*)malloc(sizeof(unsigned char)*OWidth*OHeight);
		Scailing(Img->Alpha, Img->Width, Img->Height, temp, OWidth, OHeight);
		free(Img->Alpha);
		Img->Alpha=temp;
	}

	Img->Width=OWidth;
	Img->Height=OHeight;
}



void Denoising_medianfilter(struct bmpD* Img, unsigned int Area)
{

	unsigned char *temp;

	temp=(unsigned char*)malloc(sizeof(unsigned char)*Img->Width*Img->Height);
	Filter_median(Img->C.RY, Img->Width, Img->Height, temp,Area);
	free(Img->C.RY);
	Img->C.RY=temp;


	temp=(unsigned char*)malloc(sizeof(unsigned char)*Img->Width*Img->Height);
	Filter_median(Img->C.GU, Img->Width, Img->Height, temp,Area);
	free(Img->C.GU);
	Img->C.GU=temp;

	temp=(unsigned char*)malloc(sizeof(unsigned char)*Img->Width*Img->Height);
	Filter_median(Img->C.BV, Img->Width, Img->Height, temp,Area);
	free(Img->C.BV);
	Img->C.BV=temp;

}


void Denoising_averangefilter(struct bmpD* Img,unsigned int Area)
{
	unsigned char *temp;

	temp=(unsigned char*)malloc(sizeof(unsigned char)*Img->Width*Img->Height);
	Filter_avg(Img->C.RY, Img->Width, Img->Height, temp, Area);
	free(Img->C.RY);
	Img->C.RY=temp;

	temp=(unsigned char*)malloc(sizeof(unsigned char)*Img->Width*Img->Height);
	Filter_avg(Img->C.GU, Img->Width, Img->Height, temp, Area);
	free(Img->C.GU);
	Img->C.GU=temp;

	temp=(unsigned char*)malloc(sizeof(unsigned char)*Img->Width*Img->Height);
	Filter_avg(Img->C.GU, Img->Width, Img->Height, temp, Area);
	free(Img->C.GU);
	Img->C.GU=temp;


}

void Denoising_gaussianfilter(struct bmpD *Img, unsigned int Area)
{

	double *tmp;
	tmp=malloc(sizeof(double)*Img->Width*Img->Height);

printf("into blur R\n");
	Filter_gaussian(Img->C.RY, Img->Width, Img->Height, tmp, Area);
	TypeTrans_DtUC(tmp, Img->Width, Img->Height, Img->C.RY);

printf("into blur G\n");
	Filter_gaussian(Img->C.GU, Img->Width, Img->Height, tmp, Area);
	TypeTrans_DtUC(tmp, Img->Width, Img->Height, Img->C.GU);

printf("into blur B\n");
	Filter_gaussian(Img->C.BV, Img->Width, Img->Height, tmp, Area);
	TypeTrans_DtUC(tmp, Img->Width, Img->Height, Img->C.BV);

	free(tmp);
}

double PSNR_RGB(struct bmpD *Img1, struct bmpD* Img2)
{
	double psnr_rgb=0;

	psnr_rgb+=FindNumber_PSNR(Img1->C.RY,Img2->C.RY,Img1->Width*Img1->Height);
	psnr_rgb+=FindNumber_PSNR(Img1->C.GU,Img2->C.GU,Img1->Width*Img1->Height);
	psnr_rgb+=FindNumber_PSNR(Img1->C.BV,Img2->C.BV,Img1->Width*Img1->Height);

	return psnr_rgb;

}

void Histogram_EQRGB(struct bmpD *Img)
{

	Intensity_hisEQ(Img->C.RY,Img->Width,Img->Height);
	Intensity_hisEQ(Img->C.GU,Img->Width,Img->Height);
	Intensity_hisEQ(Img->C.BV,Img->Width,Img->Height);

}

void Histogram_EQImg(struct bmpD *Img)
{
	int i,j;
	unsigned int hisR[256], hisG[256], hisB[256], hisT[256],mapping[256];


	for(i=0;i<256;i++)
	{
		hisR[i]=0;
		hisG[i]=0;
		hisB[i]=0;
	}
	Count_histogram( Img->C.RY, Img->Width*Img->Height, hisR);
	Count_histogram( Img->C.GU, Img->Width*Img->Height, hisG);
	Count_histogram( Img->C.BV, Img->Width*Img->Height, hisB);

	for(i=0;i<256;i++)
	{
		hisT[i]=hisR[i]+hisG[i]+hisB[i];
if(i%10==0)
printf("\nhisT[%3d] =",i);
printf(" %10d,",hisT[i]);
	}

	for(i=1;i<256;i++)
		hisT[i]+=hisT[i-1];

	j=0;
	for(i=0;i<256;i++)
	{
		while(hisT[i]>(j+1)*Img->Width*Img->Height*3/256)
			j++;
		mapping[i]=j;
//printf("histT[%3d] = %10d, equal = %3d*%7d = %10d\n",i,hisT[i],j+1,Img->Width*Img->Height*3/256,(j+1)*(Img->Width*Img->Height*3/256));
printf("mapping[%3d] = %3d\n",i,mapping[i]);
	}

	for(i=0;i<Img->Width*Img->Height;i++)
	{
		Img->C.RY[i]=mapping[Img->C.RY[i]];
		Img->C.GU[i]=mapping[Img->C.GU[i]];
		Img->C.BV[i]=mapping[Img->C.BV[i]];
	}

}

void RemappingRGB(struct bmpD *Img)
{
	int i,j;
	unsigned int mapping[256];
	double Scale, smooth=1;

	Scale=128./log(128*smooth);

	for(i=0;i<128;i++)
{
		mapping[i] = Scale*log(i*smooth+1);
		printf("[%3d] = %lf\n", i, Scale*log(i*smooth+1));
}
	for(i=128;i<256;i++)
{
		mapping[i] = 255-Scale*log((255-i)*smooth+1);
		printf("[%3d] = %lf\n", i,255-Scale*log((255-i)*smooth+1));
}

	for(i=0;i<Img->Width*Img->Height;i++)
	{
		Img->C.RY[i]=mapping[Img->C.RY[i]];
		Img->C.GU[i]=mapping[Img->C.GU[i]];
		Img->C.BV[i]=mapping[Img->C.BV[i]];
	}

}

void RemappingY(struct bmpD *Img)
{
	int i,j;
	double mapping[256], *Y, *ratio;
	double Scale, smooth=1;

	Scale=128./log(128*smooth);

	for(i=0;i<128;i++)
{
		mapping[i] = Scale*log(i*smooth+1);
		printf("[%3d] = %lf\n", i, Scale*log(i*smooth+1));
}
	for(i=128;i<256;i++)
{
		mapping[i] = 255-Scale*log((255-i)*smooth+1);
		printf("[%3d] = %lf\n", i,255-Scale*log((255-i)*smooth+1));
}

	Y=malloc(sizeof(double)*Img->Width*Img->Height);
	ColorTrans_RGBtY(&(Img->C), Img->Width, abs(Img->Height), Y);

	ratio=malloc(sizeof(double)*Img->Width*abs(Img->Height));
	for(i=0;i<Img->Width*abs(Img->Height);i++)
		ratio[i]=mapping[(int)Y[i]]/Y[i];

	for(i=0;i<Img->Width*abs(Img->Height);i++)
	{
		if(Img->C.RY[i]*ratio[i]>255)
			Img->C.RY[i]=255;
		else
			Img->C.RY[i]=Img->C.RY[i]*ratio[i];

		if(Img->C.GU[i]*ratio[i]>255)
			Img->C.GU[i]=255;
		else
			Img->C.GU[i]=Img->C.GU[i]*ratio[i];

		if(Img->C.BV[i]*ratio[i]>255)
			Img->C.BV[i]=255;
		else
			Img->C.BV[i]=Img->C.BV[i]*ratio[i];
	}


}

void YUV420VtRGBgray(char *fileN, struct bmpD *Img, unsigned int fn)
{
	int i;

	YUV420RFunc(fileN, &(Img->C), Img->Width, abs(Img->Height), fn);

	for(i=0;i<Img->Width*abs(Img->Height);i++)
	{
		Img->C.GU[i]=Img->C.RY[i];
		Img->C.BV[i]=Img->C.RY[i];
	}

}

void SSIM_block(unsigned char *In1, unsigned char *In2, unsigned int Width, unsigned int Height, unsigned int BlockSize)
{
	int i,j;
	unsigned char *tmp1,*tmp2;

	tmp1 = malloc(sizeof(unsigned char)*BlockSize*BlockSize);
	tmp2 = malloc(sizeof(unsigned char)*BlockSize*BlockSize);

	for(i=0;i<Height/BlockSize;i++)
	{
		printf("\nline(%3d,%3d) = \n", j*BlockSize, i*BlockSize);
		for(j=0;j<Width/BlockSize;j++)
		{
			BlockDraw_mirror(In1, Width, Height, j*BlockSize, i*BlockSize, tmp1, BlockSize, BlockSize);
			BlockDraw_mirror(In2, Width, Height, j*BlockSize, i*BlockSize, tmp2, BlockSize, BlockSize);

			printf("%5lf, ", FindNumber_SSIM(tmp1,tmp2,BlockSize*BlockSize));

		}
	}


}
