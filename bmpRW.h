#include<stdbool.h>

#include"./dataOP.h"

struct bmpD
{
    char ID[2];
    int  sizeT;
    int reserve;
    int  offsetRGB;

    int sizeInfo;
    int Width;
    int Height;
    short int planes;
    short int BPP;
    int compression;
    int sizeD;
    int Hresolution;
    int Vresolution;
    int UsedColors;
    int ImportColors;

	unsigned char *Colors;

	struct charcontainer_3 C;
	unsigned char *Alpha;
};

void bmpRFunc(char*,struct bmpD**);
void bmpWFunc(char*,struct bmpD*, bool);

void headerPrint(struct bmpD*);

//container per frame, Width, Height, frame number
void YUV420RFunc(char*, struct charcontainer_3*, unsigned int, unsigned int, unsigned int);




