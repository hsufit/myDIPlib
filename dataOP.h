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

//put block on (X,Y) to (X+OWidth, Y+OHeight)
void BlockInsert(unsigned char*, int, int, int, int, unsigned char*, int, int);

//up scailing and down scailing
//input, input width, input height, output, output width, output height
void Scailing(unsigned char*, int, int, unsigned char*, int, int);


//Filter using median algorithm*********************************start
	//input, array size
void Sort_bubble(unsigned char*, unsigned int);

	//input, array size
unsigned char FindNumber_medium(unsigned char*, unsigned int);

	//find the median number near every point
	//input, input width, input height, output, area size(1+2*n for each edge)
void Filter_median(unsigned char*, int, int, unsigned char*, unsigned int);

//Filter using median algorithm*********************************end

//Filter using avf algorithm************************************start
	//input, array size
unsigned char FindNumber_avg(unsigned char*, unsigned int);

	//find the averange number near every point
	//input, input width, input height, output, area size(1+2*n for each edge)
void Filter_avg(unsigned char*, int, int, unsigned char*, unsigned int);

//Filter using avf algorithm************************************end

//compare two data to get MSE
double MSE(unsigned char*, unsigned char*, unsigned int);
//compare two data to get PSNR
double PSNR(unsigned char*, unsigned char*, unsigned int);



//Transform using wavelet***************************************start
void Transform_wavelet(unsigned char*, unsigned int, unsigned int, double*);
//Transform using wavelet***************************************end

//data type transform
void TypeTrans_DtUC(double*, unsigned int, unsigned int, unsigned char*);

void ColorTrans_RGBtY(struct charcontainer_3*, unsigned int, unsigned int, double*);


