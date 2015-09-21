#include<stdio.h>
#include<stdlib.h>

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



double PSNR_RGB(struct bmpD *Img1, struct bmpD* Img2)
{
	double psnr_rgb=0;

	psnr_rgb+=PSNR(Img1->C.RY,Img2->C.RY,Img1->Width*Img1->Height);
	psnr_rgb+=PSNR(Img1->C.GU,Img2->C.GU,Img1->Width*Img1->Height);
	psnr_rgb+=PSNR(Img1->C.BV,Img2->C.BV,Img1->Width*Img1->Height);

	return psnr_rgb;

}


