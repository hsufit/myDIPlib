#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"./dataOP.h"

void BlockDraw_mirror(unsigned char *In, int IWidth, int IHeight, int X, int Y, unsigned char *Out, int OWidth, int OHeight)
{
	int i,j,x,y;

	for(i=0;i<OHeight;i++)
		for(j=0;j<OWidth;j++)
		{
			y=Y+i;
			x=X+j;

			if(x<0)
				x=abs(x)-1;
			else if(x>IWidth-1)
					x=IWidth-abs(x-IWidth+1);

			if(y<0)
				y=abs(y)-1;
			else if(y>IHeight-1)
					y=IHeight-abs(y-IHeight+1);

			Out[i*OWidth+j]=In[y*IWidth+x];
		}
}



void BlockInsert(unsigned char *In, int IWidth, int IHeight, int X, int Y, unsigned char *Out, int OWidth, int OHeight)
{
	int i,j;

	for(i=0;i<OHeight;i++)
		for(j=0;j<OWidth;j++)
		{
			if((X+j)<IWidth && (Y+i)<IHeight)
			In[(Y+i)*IWidth+X+j]=Out[i*OWidth+j];
		}
}

void Scailing(unsigned char *In, int IWidth, int IHeight, unsigned char *Out, int OWidth, int OHeight)
{
	int i, j, X1, Y1, X2, Y2;
	double x, y;
	double p, q, r, s, a, b, c, d, v;

	for(i=0;i<OHeight;i++)
		for(j=0;j<OWidth;j++)
		{
			x=j*((double)IWidth/OWidth);
			y=i*((double)IHeight/OHeight);

			X1=floor(x);
			Y1=floor(y);
			if(X1+1<IWidth)
				X2=X1+1;
			else
				X2=X1;
			if(Y1+1<IHeight)
				Y2=Y1+1;
			else
				Y2=Y1;


			p=In[Y1*IWidth+X1];//v(X,Y)
			q=In[Y1*IWidth+X2];//v(X+1,Y)
			r=In[Y2*IWidth+X1];//v(X,Y+1)
			s=In[Y2*IWidth+X2];//v(X+1;Y+1)

			//count the coefficient
			a=q-p;
			b=r-p;
			c=p+s-q-r;
			d=p;

			v=a*(x-X1)+b*(y-Y1)+c*(x-X1)*(y-Y1)+d;

//printf("v(%d,%d) = %lf, %lf, %lf, %lf\nvalue = %lf\na=%lf, b=%lf, c=%lf, d=%lf\n",X1,Y1,p,q,r,s,v,a,b,c,d);

			Out[i*OWidth+j]=v;

		}
}


void Sort_bubble(unsigned char *In, unsigned int ArraySize)
{
	int i,j;
	unsigned char temp;

	if(ArraySize<2)
	{
		printf("array size can't smaller then 2!");
	}
	else
	{
		for(i=0;i<ArraySize-1;i++)
			for(j=0;j<ArraySize-1-i;j++)
			{
				if(In[j]<In[j+1])
				{
					temp=In[j];
					In[j]=In[j+1];
					In[j+1]=temp;
				}
			}
	}
}

unsigned char FindNumber_medium(unsigned char *In, unsigned int ArraySize)
{
	int i;

	unsigned char *temp;
	int r;

	if(ArraySize<2)
	{
		printf("array size can't smaller then 2!");
		return 0;
	}

	temp=(unsigned char*)malloc(sizeof(unsigned char)*ArraySize);

	for(i=0;i<ArraySize;i++)
		temp[i]=In[i];

	Sort_bubble(temp,ArraySize);

	r=temp[ArraySize/2];
	free(temp);

	return r;
}


void Filter_median(unsigned char *In, int Width, int Height, unsigned char *Out, unsigned int Size)
{
	int i,j;

	unsigned char *temp;
	unsigned int N;

	N=Size*2+1;
	temp=(unsigned char*)malloc(sizeof(unsigned char)*N*N);

	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			BlockDraw_mirror(In,Width,Height,j-Size,i-Size,temp,N,N);
			Out[i*Width+j]=FindNumber_medium(temp,N*N);
		}
	free(temp);
}


unsigned char FindNumber_avg(unsigned char *In, unsigned int ArraySize)
{
	int i;

	double avg=0;

	for(i=0;i<ArraySize;i++)
		avg+=In[i];

	avg/=ArraySize;

	return (unsigned char)avg;
}



void Filter_avg(unsigned char *In, int Width, int Height, unsigned char *Out, unsigned int Size)
{
	int i,j;

	unsigned char *temp;
	unsigned int N;

	N=Size*2+1;
	temp=(unsigned char*)malloc(sizeof(unsigned char)*N*N);
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			BlockDraw_mirror(In, Width, Height, j-Size, i-Size, temp, N, N);
			Out[i*Width+j]=FindNumber_avg(temp,N*N);
		}
	free(temp);

}



double MSE(unsigned char *In1, unsigned char*In2, unsigned int ArraySize)
{
	int i;

	double mse=0;
	int sqrt;

	for(i=0;i<ArraySize;i++)
	{
		sqrt=((int)In1[i]-In2[i])*((int)In1[i]-In2[i]);
		mse+=sqrt;
	}

	mse/=ArraySize;


	return mse;
}


double PSNR(unsigned char*In1, unsigned char*In2, unsigned int ArraySize)
{
	int i;
	double mse, psnr;

	mse=MSE(In1,In2,ArraySize);

	psnr=10*log10(255*255/mse);

	return psnr;
}

