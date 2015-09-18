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

	Img->Width=OWidth;
	Img->Height=OHeight;
}

