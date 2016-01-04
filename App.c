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
	int i;
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
	int i;
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


void LAB_ABrotate(struct doublecontainer_3 *In, unsigned int Width, unsigned int Height, double arc, struct doublecontainer_3 *Out)
{
	int i;

	for(i=0;i<Width*Height;i++)
	{
		Out->A[i] = In->A[i];
		Out->B[i] = In->B[i]*cos(arc)+In->C[i]*sin(arc);
		Out->C[i] = In->C[i]*cos(arc)-In->B[i]*sin(arc);
	}

}

void LAB_ABShift(struct doublecontainer_3 *In, unsigned int Width, unsigned int Height, double SA, double SB, struct doublecontainer_3 *Out)
{
	int i;

	for(i=0;i<Width*Height;i++)
	{
		Out->A[i] = In->A[i];
Out->B[i] = In->B[i];
Out->C[i] = 15;//In->C[i]*0.2;
/*		if(abs(In->B[i]+SA)<500)
			Out->B[i] = In->B[i]+SA;
		else
			Out->B[i] = In->B[i]+SA>0? 500:-500;
		if(abs(In->C[i]+SB)<200)
			Out->C[i] = In->C[i]+SB;
		else
			Out->C[i] = In->C[i]+SB>0? 200:-200;
*/		
	}

}

void LeastSquare_RSRatLAB(struct doublecontainer_3 *In, unsigned int Width, unsigned int Height, struct doublecontainer_3 *Out)
{
	int i,j,k,l,m;

	unsigned int position[48];

	struct doublecontainer_3 *RefxyY, *RefXYZ, *RefLAB, *ImgLAB, *testLAB;
	double DiffWX, DiffWY, minMSE=5000000, MSE;
	int R1, SX, SY, R2;

	FILE *fp;

	fp = fopen("./image1_board.txt","r");
	for(i=0;i<24;i++)
	{
		fscanf(fp,"%d,%d",&(position[i*2]),&(position[i*2+1]));
		printf("color point%2d = (%3d,%3d)\n",i,position[i*2],position[i*2+1]);
	}
	fclose(fp);
	fp = NULL;

	RefxyY = malloc(sizeof(struct doublecontainer_3));
	RefxyY->A = malloc(sizeof(double)*24);
	RefxyY->B = malloc(sizeof(double)*24);
	RefxyY->C = malloc(sizeof(double)*24);
	//read the 24 reference point of xyY
	fp = fopen("./goldenxyY","r");
	for(i=0;i<24;i++)
	{
		fscanf(fp,"%lf %lf %lf",&(RefxyY->A[i]),&(RefxyY->B[i]),&(RefxyY->C[i]));
		//print the referenced color
		printf("color[%2d] : %lf, %lf, %lf\n", i,(RefxyY->A[i]),(RefxyY->B[i]),(RefxyY->C[i]));
	}
	fclose(fp);

	RefXYZ = malloc(sizeof(struct doublecontainer_3));
	RefXYZ->A = malloc(sizeof(double)*24);
	RefXYZ->B = malloc(sizeof(double)*24);
	RefXYZ->C = malloc(sizeof(double)*24);
	//transform xyY to XYZ
	for(i=0;i<24;i++)
	{
		RefXYZ->A[i] = RefxyY->C[i]*RefxyY->A[i]/RefxyY->B[i];
		RefXYZ->B[i] = RefxyY->C[i];
		RefXYZ->C[i] = RefxyY->C[i]*(1-RefxyY->A[i]-RefxyY->B[i])/RefxyY->B[i];
	}

	RefLAB = malloc(sizeof(struct doublecontainer_3));
	RefLAB->A = malloc(sizeof(double)*24);
	RefLAB->B = malloc(sizeof(double)*24);
	RefLAB->C = malloc(sizeof(double)*24);
	//transform XYZ to LAB
	ColorTrans_XYZtLAB(RefXYZ, 24, 1, RefLAB);

	ImgLAB = malloc(sizeof(struct doublecontainer_3));
	ImgLAB->A = malloc(sizeof(double)*24);
	ImgLAB->B = malloc(sizeof(double)*24);
	ImgLAB->C = malloc(sizeof(double)*24);
	//draw colors on the board
	for(i=0;i<24;i++)
	{
		ImgLAB->A[i] = In->A[(Height-position[i*2+1]-1)*Width+position[i*2]];
		ImgLAB->B[i] = In->B[(Height-position[i*2+1]-1)*Width+position[i*2]];
		ImgLAB->C[i] = In->C[(Height-position[i*2+1]-1)*Width+position[i*2]];
		printf("point%3d = LAB(%lf,%lf,%lf) from (%3d,%3d)\n",i ,ImgLAB->A[i], ImgLAB->B[i], ImgLAB->C[i],position[i*2],Height-position[i*2+1]-1);
	}

	DiffWX = sqrt(pow(ImgLAB->B[19]-RefLAB->B[19],2)+pow(ImgLAB->C[19]-RefLAB->C[19],2));
	DiffWY = DiffWX;

	testLAB = malloc(sizeof(struct doublecontainer_3));
	testLAB->A = malloc(sizeof(double)*24);
	testLAB->B = malloc(sizeof(double)*24);
	testLAB->C = malloc(sizeof(double)*24);
	for(i=0;i<1/*360*/;i++)
	{
	//printf("testing R1 = %3d, SX = %3d, SY = %3d, R2 = %3d\n minMSE = %lf\n", i, j, k, l,minMSE);
		for(j=0;j<61;j++)
		{
			for(k=0;k<61;k++)
			{
				for(l=0;l<1/*360*/;l++)
				{
	printf("Ref LAB = (%10lf,%10lf,%10lf)\n", RefLAB->A[18], RefLAB->B[18], RefLAB->C[18]);
					LAB_ABrotate(RefLAB, 24, 1, i*M_PI/180, testLAB);
	printf("testing R1 LAB = (%10lf,%10lf,%10lf)\n", testLAB->A[18], testLAB->B[18], testLAB->C[18]);
					LAB_ABShift(testLAB, 24, 1, -DiffWX+j*DiffWX/30, -DiffWY+k*DiffWY/30, testLAB);
	printf("testing S LAB = (%10lf,%10lf,%10lf)\n", testLAB->A[18], testLAB->B[18], testLAB->C[18]);
					LAB_ABrotate(testLAB, 24, 1, l*M_PI/180, testLAB);
	printf("testing R2 LAB = (%10lf,%10lf,%10lf)\n", testLAB->A[18], testLAB->B[18], testLAB->C[18]);
					MSE=0;
					for(m=0;m<24;m++)
					{
						MSE+=pow(testLAB->B[m]-ImgLAB->B[m],2)+pow(testLAB->C[m]-ImgLAB->C[m],2);
					}
	printf("testing MSE = %lf, SX = %3d, SY = %3d, R2 = %3d\n", MSE, j, k, l);
	
					if(MSE<minMSE)
					{
						minMSE=MSE;
						R1=i;
						SX=j;
						SY=k;
						R2=l;
					}
				}
			}
		}
	}

	printf("\nminMSE = %lf\nRotate arg 1 = %d\nshift = (%3d,%3d)\nRotate arg 2 = %d\n",minMSE, R1,SX,SY,R2);

	//LAB_ABrotate(In, Width, Height, -R2*M_PI/180, Out);
	//LAB_ABShift(In, Width, Height, DiffWX-SX*DiffWX/30, DiffWY-SY*DiffWY/30, Out);
	LAB_ABShift(In, Width, Height, 0, 0, Out);
	//LAB_ABrotate(Out, Width, Height, -R1*M_PI/180, Out);

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
