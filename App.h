#include"./bmpRW.h"

//HW1
void Scailing_RGB(struct bmpD*, int, int);

void Denoising_medianfilter(struct bmpD*,unsigned int);
void Denoising_averangefilter(struct bmpD*,unsigned int);

double PSNR_RGB(struct bmpD*,struct bmpD*);

//HW2
//for RGB independenly histogram
void Histogram_EQRGB(struct bmpD*);
//for Image total histogram
void Histogram_EQImg(struct bmpD*);
//gaussian filter
void Denoising_gaussianfilter(struct bmpD*, unsigned int Area);
void RemappingRGB(struct bmpD*);
void RemappingY(struct bmpD*);

//Others
void YUV420VtRGBgray(char*, struct bmpD*, unsigned int);
	//segment the image and count the SSIM using N*N block, not pix by pix
void SSIM_block(unsigned char*, unsigned char*, unsigned int, unsigned int, unsigned int);





