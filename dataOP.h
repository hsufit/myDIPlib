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

//********************************************
//function name style : ManeTitle_type
//********************************************


//draw block on (X,Y) to (X+OWidth, Y+OHeight)
void BlockDraw_mirror(unsigned char*, int, int, int, int, unsigned char*, int, int);

//put block on (X,Y) to (X+OWidth, Y+OHeight)
void BlockInsert(unsigned char*, int, int, int, int, unsigned char*, int, int);

//up scailing and down scailing
void Scailing(unsigned char*, int, int, unsigned char*, int, int);
















