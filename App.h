#include"./bmpRW.h"

void Scailing_RGB(struct bmpD*, int, int);

void Denoising_medianfilter(struct bmpD*,unsigned int);
void Denoising_averangefilter(struct bmpD*,unsigned int);

double PSNR_RGB(struct bmpD*,struct bmpD*);

