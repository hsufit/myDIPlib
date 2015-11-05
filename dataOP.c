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


void BlockDraw_mirrorDouble(double *In, unsigned int IWidth, unsigned int IHeight, unsigned int X, unsigned int Y, double *Out, unsigned int OWidth, unsigned int OHeight)
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

void BlockInsertDouble(double *In, int IWidth, int IHeight, int X, int Y, double *Out, int OWidth, int OHeight)
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

void Intensity_hisEQ(unsigned char *In, unsigned int Width, unsigned int Height)
{
	int i,j;
	unsigned int his[256],mapping[256],counter=0;

	Count_histogram( In, Width*Height, his);

	//count his PDF into CDF
	for(i=1;i<256;i++)
		his[i]+=his[i-1];

	//find mapptng
	j=0;
	for(i=0;i<256;i++)
	{
		while(his[i]>(j+1)*Width*Height/256 && j<256)
			j++;

		mapping[i]=j;
//printf("i:%3d=%3d\n",i,mapping[i]);
	}

	//mapping
	for(i=0;i<Width*Height;i++)
	{
		In[i]=mapping[In[i]];
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


double FindNumber_avg(unsigned char *In, unsigned int ArraySize)
{
	int i;

	double avg=0;

	for(i=0;i<ArraySize;i++)
		avg+=In[i];

	avg/=ArraySize;

	return avg;
}

double FindNumber_avgDouble(double *In, unsigned int ArraySize)
{
	int i;

	double avg=0;

	for(i=0;i<ArraySize;i++)
		avg+=In[i];

	avg/=ArraySize;

	return avg;
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
			Out[i*Width+j]=(unsigned char)FindNumber_avg(temp,N*N);
		}
	free(temp);

}

double Gaussian(unsigned char *In, int Width, int Height)
{
	int i,j, k, l, x, y;
	double result=0, tGx=0, tGy=0, vx, vy, Gx, Gy;

	x=Width/2;
	y=Height/2;

	vx=Width/3.;
	vy=Height/3.;

	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{

		if(Width==1)
			Gx=1;
		else if(Width%2)
			Gx=(1/(vx*sqrt(2*M_PI)))*exp(-1*pow((x-j),2)/(2*vx*vx));
		else
			Gx=(1/(vx*sqrt(2*M_PI)))*exp(-1*pow((x+0.5-j),2)/(2*vx*vx));

		if(Height==1)
			Gy=1;
		else if(Height%2)
			Gy=(1/(vy*sqrt(2*M_PI)))*exp(-1*pow((y-i),2)/(2*vy*vy));
		else
			Gy=(1/(vy*sqrt(2*M_PI)))*exp(-1*pow((y+0.5-i),2)/(2*vy*vy));

			result+=In[i*Width+j]*Gx*Gy;
/*
if(i==0)
	tGx+=Gx;
if(j==0)
	tGy+=Gy;
printf("In(%3d, %3d) = %5d, Gx= %5lf, Gy= %5lf\n",j,i,In[i*Width+j],Gx,Gy);
*/
		}

//printf("result = %5lf, tGx = %5lf, tGy = %5lf\n", result, tGx, tGy);

	return result;

}

double GaussianDouble(double *In, int Width, int Height)
{
	int i,j, k, l, x, y;
	double result=0, tGx=0, tGy=0, vx, vy, Gx, Gy;

	x=Width/2;
	y=Height/2;

	vx=Width/3.;
	vy=Height/3.;

	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{

		if(Width==1)
			Gx=1;
		else if(Width%2)
			Gx=(1/(vx*sqrt(2*M_PI)))*exp(-1*pow((x-j),2)/(2*vx*vx));
		else
			Gx=(1/(vx*sqrt(2*M_PI)))*exp(-1*pow((x+0.5-j),2)/(2*vx*vx));

		if(Height==1)
			Gy=1;
		else if(Height%2)
			Gy=(1/(vy*sqrt(2*M_PI)))*exp(-1*pow((y-i),2)/(2*vy*vy));
		else
			Gy=(1/(vy*sqrt(2*M_PI)))*exp(-1*pow((y+0.5-i),2)/(2*vy*vy));

			result+=In[i*Width+j]*Gx*Gy;
/*
if(i==0)
	tGx+=Gx;
if(j==0)
	tGy+=Gy;
printf("In(%3d, %3d) = %5d, Gx= %5lf, Gy= %5lf\n",j,i,In[i*Width+j],Gx,Gy);
*/
		}

//printf("result = %5lf, tGx = %5lf, tGy = %5lf\n", result, tGx, tGy);

	return result;

}

void Filter_gaussian(unsigned char *In, int Width, int Height, double *Out, int Size)
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
			Out[i*Width+j]=Gaussian(temp,N,N);
		}
	free(temp);

}


void Filter_gaussianDouble(double *In, int Width, int Height, double *Out, int Size)
{
	int i,j;

	double *temp;
	unsigned int N;

	N=Size*2+1;
	temp=(double*)malloc(sizeof(double)*N*N);

	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			BlockDraw_mirrorDouble(In, Width, Height, j-Size, i-Size, temp, N, N);
			Out[i*Width+j]=GaussianDouble(temp,N,N);
		}
	free(temp);

}

double FindNumber_MSE(unsigned char *In1, unsigned char*In2, unsigned int ArraySize)
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


double FindNumber_PSNR(unsigned char*In1, unsigned char*In2, unsigned int ArraySize)
{
	int i;
	double mse, psnr;

	mse=FindNumber_MSE(In1,In2,ArraySize);

	psnr=10*log10(255*255/mse);

	return psnr;
}

double FindNumber_VAR(unsigned char *In,unsigned int ArraySize)
{
	int i;
	double *SqrDiff,var,avg;

	avg=FindNumber_avg(In, ArraySize);

	SqrDiff = malloc(sizeof(double)*ArraySize);
	for(i=0;i<ArraySize;i++)
		SqrDiff[i]=pow(In[i]-avg,2);

	var=FindNumber_avgDouble(SqrDiff,ArraySize);

	free(SqrDiff);

	return var;
}

double FindNumber_CoVAR(unsigned char *In1, unsigned char *In2,unsigned int ArraySize)
{
	int i;
	double *CoDiff, covar, avg1, avg2;

	avg1=FindNumber_avg(In1, ArraySize);
	avg2=FindNumber_avg(In2, ArraySize);

	CoDiff = malloc(sizeof(double)*ArraySize);
	for(i=0;i<ArraySize;i++)
		CoDiff[i]=(In1[i]-avg1)*(In2[i]-avg2);

	covar=FindNumber_avgDouble(CoDiff,ArraySize);

	free(CoDiff);

	return covar;
}

double FindNumber_SSIM(unsigned char *In1, unsigned char *In2, unsigned int ArraySize)
{
	double avg1, avg2, var1, var2, covar, SSIM;
			//C1=(k1*L)^2  C2=(k2*L)^2 L=2^8-1 k1=0.01 k2=0.03
	double C1=0.01*0.01*255*255, C2=0.03*0.03*255*255;
	double Luminance,Contrast,Structure;

	avg1=FindNumber_avg(In1,ArraySize);
	avg2=FindNumber_avg(In2,ArraySize);
//printf("avg = %5lf, %5lf\n",avg1,avg2);

	var1=FindNumber_VAR(In1,ArraySize);
	var2=FindNumber_VAR(In2,ArraySize);
//printf("var = %5lf, %5lf\n",var1,var2);

	covar=FindNumber_CoVAR(In1, In2, ArraySize);
//printf("covar = %5lf\n",covar);

	Luminance = (2*avg1*avg2+C1)/(avg1*avg1+avg2*avg2+C1);
	Contrast = (2*sqrt(var1)*sqrt(var2)+C2)/(var1+var2+C2);
	Structure = (2*covar+C2)/(2*sqrt(var1)*sqrt(var2)+C2);
printf("Luminance = %10lf\n",Luminance);
printf("Contrast = %10lf\n",Contrast);
printf("Structure = %10lf\n",Structure);

	SSIM = Luminance*Contrast*Structure;

	return SSIM;
}

void Transform_wavelet1D(unsigned char *In, unsigned int ArraySize, double *OutL, double *OutH)
{
	int i,j;

	//padding same value of the boundary for out of range, so ArraySize-1
	for(i=0;i<ArraySize-1;i++)
	{
		OutL[i]=(In[i]+In[i+1])/2.;
		OutH[i]=(In[i]-In[i+1])/2.;
	}
	//put the value into Out[ArraySize]
	OutL[i]=In[i];
	OutH[i]=0;

	return;
}

void Transform_wavelet1DDouble(double *In, unsigned int ArraySize, double *OutL, double *OutH)
{
	int i,j;

	//padding same value of the boundary for out of range, so ArraySize-1
	for(i=0;i<ArraySize-1;i++)
	{
		OutL[i]=(In[i]+In[i+1])/2.;
		OutH[i]=(In[i]-In[i+1])/2.;
	}
	//put the value into Out[ArraySize]
	OutL[i]=In[i];
	OutH[i]=0;

	return;
}

void Transform_wavelet(unsigned char *In, unsigned int Width, unsigned int Height, double *Out)
{
	int i,j;
	double *tmp1, *tmp2;

	if(Width%2 | Height%2)
	{
		printf("error size!\n");
		return;
	}

	tmp1=malloc(sizeof(double)*Width*Height);
	tmp2=malloc(sizeof(double)*Width*Height);

//vertical
	for(i=0;i<Height;i++)
		for(j=0;j<Width/2;j++)
		{
			tmp1[i*Width+j]=(double)In[i*Width+j*2]+In[i*Width+j*2+1];
			tmp1[i*Width+j+Width/2]=(double)In[i*Width+j*2]-In[i*Width+j*2+1];
		}

//horizontal
	for(i=0;i<Height/2;i++)
		for(j=0;j<Width;j++)
		{
			tmp2[i*Width+j]=(double)tmp1[i*2*Width+j]+tmp1[(i*2+1)*Width+j];
			tmp2[(i+Height/2)*Width+j]=(double)tmp1[i*2*Width+j]-tmp1[(i*2+1)*Width+j];
		}
	free(tmp1);
	
//testing data print for debug
/*
	for(i=0;i<Height/2;i++)
		for(j=0;j<Width/2;j++)
		{
if(i<8 && (j<10))
{
			printf("(%3d, %3d)\n", j*2, i*2);
			printf("v(x,y) = %3d, %3d, %3d, %3d\n",In[i*2*Width+j*2], In[i*2*Width+j*2+1], In[(i*2+1)*Width+j*2], In[(i*2+1)*Width+j*2+1]);
			printf("w(x,y) = %5lf, %5lf, %5lf, %5lf\n",tmp2[i*Width+j], tmp2[i*Width+j+Width/2], tmp2[(i+Height/2)*Width+j], tmp2[(i+Height/2)*Width+j+Width/2]);
}
		}
*/

//normalize
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
			Out[i*Width+j] = tmp2[i*Width+j]/4;
	free(tmp2);


}




void Transform_waveletDouble(double *In, unsigned int Width, unsigned int Height, double *Out)
{
	int i,j;
	double *tmp1, *tmp2;

	if(Width%2 | Height%2)
	{
		printf("error size!\n");
		return;
	}

	tmp1=malloc(sizeof(double)*Width*Height);
	tmp2=malloc(sizeof(double)*Width*Height);

//vertical
	for(i=0;i<Height;i++)
		for(j=0;j<Width/2;j++)
		{
			tmp1[i*Width+j]=In[i*Width+j*2]+In[i*Width+j*2+1];
			tmp1[i*Width+j+Width/2]=In[i*Width+j*2]-In[i*Width+j*2+1];
		}

//horizontal
	for(i=0;i<Height/2;i++)
		for(j=0;j<Width;j++)
		{
			tmp2[i*Width+j]=tmp1[i*2*Width+j]+tmp1[(i*2+1)*Width+j];
			tmp2[(i+Height/2)*Width+j]=tmp1[i*2*Width+j]-tmp1[(i*2+1)*Width+j];
		}
	free(tmp1);
	
//testing data print for debug
/*
	for(i=0;i<Height/2;i++)
		for(j=0;j<Width/2;j++)
		{
if(i<8 && (j<10))
{
			printf("(%3d, %3d)\n", j*2, i*2);
			printf("v(x,y) = %3d, %3d, %3d, %3d\n",In[i*2*Width+j*2], In[i*2*Width+j*2+1], In[(i*2+1)*Width+j*2], In[(i*2+1)*Width+j*2+1]);
			printf("w(x,y) = %5lf, %5lf, %5lf, %5lf\n",tmp2[i*Width+j], tmp2[i*Width+j+Width/2], tmp2[(i+Height/2)*Width+j], tmp2[(i+Height/2)*Width+j+Width/2]);
}
		}
*/

//normalize
	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
			Out[i*Width+j] = tmp2[i*Width+j]/4;
	free(tmp2);


}






void TypeTrans_DtUC(double *In, unsigned int Width, unsigned int Height, unsigned char *Out)
{
	int i,j;

	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			if(abs(In[i*Width+j])>255)
				printf("Warning!! : biger then 255 (%3d,%3d) = %10lf\n", j, i, In[i*Width+j]);
			Out[i*Width+j] = abs(In[i*Width+j]);
		}

}

void ColorTrans_RGBtY(struct charcontainer_3 *RGB, unsigned int Width, unsigned int Height, double *Y)
{

	int i,j;
	


	for(i=0;i<Height;i++)
		for(j=0;j<Width;j++)
		{
			Y[i*Width+j]=(RGB->RY[i*Width+j]*299+RGB->GU[i*Width+j]*587+RGB->BV[i*Width+j]*114)/1000;

//for debug
//if(i<3 && j<30)
//printf("(%3d, %3d) : %lf = %3d*0.299+%3d*0.587+%3d*0.114\n", j, i, Y[i*Width+j], RGB->RY[i*Width+j], RGB->GU[i*Width+j], RGB->BV[i*Width+j]);

		}

}


int Count_GL(double *In, unsigned int Width, unsigned int Height, double T)
{
	int i;
	unsigned int count=0;

	for(i=0;i<Width*Height;i++)
		if(In[i]>T)
			count++;

	return count;
}


void Count_histogram(unsigned char *In, unsigned int Size, unsigned int *Out)
{
	int i,j;

	//set to zero
	for(i=0;i<256;i++)
		Out[i]=0;

	//count his
	for(i=0;i<Size;i++)
		Out[In[i]]++;
}


