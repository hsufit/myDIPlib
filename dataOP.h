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
void BlockInsert(unsigned char*, int, int, int, int, unsigned char*, int, int);

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
void Transform_wavelet(unsigned char*, unsigned int, unsigned int, double*);
void Transform_waveletDouble(double*, unsigned int, unsigned int, double*);
//Transform using wavelet***************************************end

//data type transform
void TypeTrans_DtUC(double*, unsigned int, unsigned int, unsigned char*);

void ColorTrans_RGBtY(struct charcontainer_3*, unsigned int, unsigned int, double*);

//count grater then
int Count_GL(double *, unsigned int, unsigned int, double);

//count histogram
void Count_histogram(unsigned char*, unsigned int, unsigned int*);


