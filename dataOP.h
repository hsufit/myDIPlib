struct charcontainer_3
{
	unsigned char *BV;
	unsigned char *GU;
	unsigned char *RY;
};

struct intcontainer_3
{
	unsigned int *A;
	unsigned int *B;
	unsigned int *C;
};

struct doublecontainer_3
{
	double *A;
	double *B;
	double *C;
};


//********************************************
//function name style : ManeTitle_type
//********************************************


//copy block on (X,Y) to (X+OWidth, Y+OHeight)
void BlockDraw_mirror(unsigned char*, int, int, int, int, unsigned char*, int, int);
void BlockDraw_mirrorDouble(double*, unsigned int, unsigned int, unsigned int, unsigned int, double*, unsigned int, unsigned int);

//put block on (X,Y) to (X+OWidth, Y+OHeight)
//full block, sizeX, sizeY, posX, posY, insert block, sizeX, sizeY
void BlockInsert(unsigned char*, int, int, int, int, unsigned char*, int, int);
void BlockInsertDouble(double*, int, int, int, int, double*, int, int);

//up scailing and down scailing
//input, input width, input height, output, output width, output height
void Scailing(unsigned char*, int, int, unsigned char*, int, int);

//operation of intensity
void Intensity_hisEQ(unsigned char *, unsigned int, unsigned int);

//Filter using median algorithm*********************************start
	//input, array size
void Sort_bubble(unsigned char*, unsigned int);

	//input, array size
unsigned char FindNumber_medium(unsigned char*, unsigned int);
double FindNumber_maxDouble(double*, unsigned int);
double FindNumber_minDouble(double*, unsigned int);

	//find the median number near every point
	//input, input width, input height, output, area size(1+2*n for each edge)
void Filter_median(unsigned char*, int, int, unsigned char*, unsigned int);

//Filter using median algorithm*********************************end

//Filter using avg algorithm************************************start
	//input, array size
double FindNumber_avg(unsigned char*, unsigned int);
double FindNumber_avgDouble(double*, unsigned int);

	//find the averange number near every point
	//input, input width, input height, output, area size(1+2*n for each edge)
void Filter_avg(unsigned char*, int, int, unsigned char*, unsigned int);

//Filter using avg algorithm************************************end

//Filter using gaussian****************************************start
	//input, width, height
double Gaussian(unsigned char*, int, int);
double GaussianDouble(double*, int, int);

void Filter_gaussian(unsigned char*, int, int, double*, int);
void Filter_gaussianDouble(double*, int, int, double*, int);
//Filter using gaussian****************************************end

//Filter let edge be shooth for removing boundary ripple effect in IFFT
//In, IWidth, IHeight, Out, x-edgeDistance, y-edgeDistance
void Filter_BoundaryGaussianDouble(double*,unsigned int, unsigned int, double*, unsigned int, unsigned int);
//In, Width, Height, Out, vx, vy, WinerK
void Filter_WienerInverseBoundaryGaussianDouble(double*,unsigned int, unsigned int, double*, double, double, double);



//compare two data to get MSE
double FindNumber_MSE(unsigned char*, unsigned char*, unsigned int);
//compare two data to get PSNR
double FindNumber_PSNR(unsigned char*, unsigned char*, unsigned int);
//calculate varience (standard devation's square)
double FindNumber_VAR(unsigned char*, unsigned int);
//calculate covarience
double FindNumber_CoVAR(unsigned char*, unsigned char*,unsigned int);
//calculate SSIM
double FindNumber_SSIM(unsigned char*, unsigned char*, unsigned int);


//Transform using wavelet***************************************start
//original wavelet transform, will duplicate the data size and normalized by 2
void Transform_wavelet1D(unsigned char*, unsigned int, double*, double*);
void Transform_wavelet1DDouble(double*, unsigned int, double*, double*);
//fast wavelet transform
void Transform_wavelet(unsigned char*, unsigned int, unsigned int, double*);
void Transform_waveletDouble(double*, unsigned int, unsigned int, double*);
//Transform using wavelet***************************************end

//data type transform
void TypeTrans_DtUC(double*, unsigned int, unsigned int, unsigned char*);

//for input range in -50000 to 50000 mapping do a range
//Input, ArraySize, Out, Range min, Range Max
void Normalize_LinearMapping(double*, unsigned int, double*, double, double);

void ColorTrans_RGBtY(struct charcontainer_3*, unsigned int, unsigned int, double*);
//RGB color space do gamma correction and transform to XYZ color space
void ColorTrans_sRGBtXYZ(struct charcontainer_3*, unsigned int, unsigned int, struct doublecontainer_3*);
//XYZ colorspace do gamma correction and transform to RGB color space
void ColorTrans_XYZtsRGB(struct doublecontainer_3*, unsigned int, unsigned int, struct charcontainer_3*);
//XYZ colorspace transform to LAB color space
void ColorTrans_XYZtLAB(struct doublecontainer_3*, unsigned int, unsigned int, struct doublecontainer_3*);
//LAB colorspace transform to XYZ color space
void ColorTrans_LABtXYZ(struct doublecontainer_3*, unsigned int, unsigned int, struct doublecontainer_3*);

//count grater then
int Count_GL(double *, unsigned int, unsigned int, double);

//count histogram
void Count_histogram(unsigned char*, unsigned int, unsigned int*);


