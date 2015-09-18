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

			Out[i*OWidth+j]=v;

		}
}













