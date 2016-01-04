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

//HW3

//HW4
//-->main idea is using Rotata, Shift, and Rotate to find the least square solution
//LAB In data, Width, Height, Rotate at orig point coefficient,LAB Out data
void LAB_ABrotate(struct doublecontainer_3*, unsigned int, unsigned int, double, struct doublecontainer_3*);
//LAB In data, Width, Height, shift X, shift Y,LAB Out data
void LAB_ABShift(struct doublecontainer_3*, unsigned int, unsigned int, double, double, struct doublecontainer_3*);
//use least square error method to determine inverse coefficient and refine the image
void LeastSquare_RSRatLAB(struct doublecontainer_3*, unsigned int, unsigned int, struct doublecontainer_3*);


//Others
void YUV420VtRGBgray(char*, struct bmpD*, unsigned int);
	//segment the image and count the SSIM using N*N block, not pix by pix
void SSIM_block(unsigned char*, unsigned char*, unsigned int, unsigned int, unsigned int);





