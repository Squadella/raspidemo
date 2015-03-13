#include "libgmini.h"
#include "processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

//Open a ppm file and print it in the window

void open_ppm(int image[], char* file, int depth)
{

	// initialising the file
	FILE *img;
	int returnTest;
	img=fopen(file, "r");

	if (img==NULL) //if the program is unable to open the fil exit the function
	{
		printf("Unable to open file!\n");
		return;
	}

	//If the file is opened
	uint height=0;
	uint width=0;
	uint size=0;
	uint i=0;
	RGBTriplet color;
	//getting the specification of the file
	returnTest=fscanf(img, "%*[^\n]\n");
	if (returnTest!=1)
	{
	}
	returnTest=fscanf(img, "%*[^\n]\n");
	if (returnTest!=1)
	{
	}
	returnTest=fscanf(img, "%u", &width);
	if (returnTest!=1)
	{
		fclose(img);
		return;
	}
	returnTest=fscanf(img, "%u", &height);
	if (returnTest!=1)
	{
		fclose(img);
		return;
	}
	size=width*height;
	//writing the table with the new values
	for (i=0;i<size; i++)
	{
		if(fscanf(img, "%hhu", &color.b)!=1)
		{
			printf("Reading red error at index %u!\n", i);
			fclose(img);
			return;
		}
		if(fscanf(img, "%hhu", &color.r)!=1)
		{
			printf("Reading green error at index %u!\n",i);
			fclose(img);
			return;
		}
		if(fscanf(img, "%hhu", &color.g)!=1)
		{
			printf("Reading blue error at index %u!\n", i);
			fclose(img);
			return;
		}
		drawPixelIndex(i, image, color, size);
	}
	fclose(img);
}

int colorRGB(int r, int g, int b) {
	return( r<<16 | g<<8 | b );
}

// Draw a pixel with the given color
void drawPixel(Pixel pixel, int image[], long int width, long int max)
{
	unsigned int index=(pixel.y)*width+((pixel.x));
	if (index<max)
	{
		image[index]=pixel.color;
	}
}

void drawPixelIndex(int index, int image[], RGBTriplet color, long int maxb)
{
	if(index>=maxb)
	{
		return;
	}
	image[index]=colorRGB(color.r, color.g, color.b);
}

void fillImage(int image[], RGBTriplet color, int width, int maxb)
{
	int i;
	for(i = 0; i < maxb/4; i = i+1)
	{
		drawPixelIndex(i, image, color, maxb);
	}
}

void replaceImage(int image1[], int image2[], long int maxb)
{
	long int i;
	for(i=0; i<maxb; i++)
	{
		image1[i]=image2[i];
	}
}

void fadeToBlack(int image[], long int maxb)
{
	long int i;
	for (i = 0; i < maxb; i++)
	{
		if (image[i]>0)
		{
			image[i]=image[i]-1;
		}
	}
}
/*
void replaceColor(RGBTriplet color1, RGBTriplet color2, int image[], int maxb)
{
	int index;
	for(index = 0; index < maxb; index = index+1)
	{
		if((unsigned char)(image[index])==color1.b)
		{
			if ((unsigned char)(image[index+1])==color1.g)
			{
				if ((unsigned char)(image[index+2])==color1.r)
				{
					drawPixelIndex(index, image, color2, maxb);
				}
			}
		}
	}
}
*/
/*
void catImage(int *image1, int *image2, int x, int y, int direction, int height, int width)
{
	int ix, iy;
	if(y==-1)
	{
		if(direction)
		{
			for(ix=x; ix<width; ix++)
			{
				for(iy=0; iy<height; iy++)
				{
					image1[iy*width+ix]=image2[iy*width+ix];
				}
			}
		}
		else
		{
			for(ix=0; ix<x; ix++)
			{
				for(iy=0; iy<height; iy++)
				{
					image1[iy*width+ix]=image2[iy*width+ix];
				}
			}
		}
	}
	else
	{
		if (direction)
		{
			for(iy=y; iy<height; iy++)
			{
				for(ix=0; ix<width; ix++)
				{
					image1[iy*width+ix]=image2[iy*width+ix];
				}
			}
		}
		else
		{
			for(iy=0; iy<y; iy++)
			{
				for(ix=0; ix<width; ix++)
				{
					image1[iy*width+ix]=image2[iy*width+ix];
				}
			}
		}
	}
}

void catImageColor(int *image1, int *image2, int color, int height, int width)
{
	int ix, iy;
	for(ix=0; ix<width; ix++)
	{
		for(iy=0; iy<height; iy++)
		{
			if (image2[(iy*width)+ix]==color)
			{

			}
		}
	}
}
*/

/*
void drawLine(Pixel start, Pixel end, int image[], long int width, long int maxb)
{
	int dx = abs((end.x)-(start.x));
	int sx;
	if((start.x)<(end.x))
		sx=1;
	else
		sx=-1;

	int dy = -abs((end.y)-(start.y));
	int sy;
	if((start.y)<(end.y))
		sy=1;
	else
		sy=-1;

	int err = dx+dy;
	int e2=0;
	while(1)
	{
		drawPixel(start, image, width, maxb);
		if((start.x)==(end.x) && (start.y)==(end.y))
			break;
		e2=2*err;
		if(e2>=dy)
		{
			err=err+dy;
			(start.x)=(start.x)+sx;
		}
		if(e2<=dx)
		{
			err=err+dx;
			(start.y)=(start.y)+sy;
		}
	}
}


void drawCircle(const Pixel center, int radius, int image[], long int height, long int width)
{
	Pixel pixel, temp;
	int max=height*width*8;
	int err = 2-2*radius;
	pixel.x = -radius;
	pixel.y = 0;
	do
	{
		//setPixel(xm-x, ym+y); I. Quadrant
		temp.x = center.x-pixel.x;
		temp.y = center.y+pixel.y;
		temp.color=center.color;
		if (temp.x>=0 && temp.y<=height && temp.x<=width && temp.y>=0)
		{
			drawPixel(temp, image, width, max);
		}

		//setPixel(xm-y, ym-x);   II. Quadrant
		temp.x = center.x-pixel.y;
		temp.y = center.y-pixel.x;
		temp.color=center.color;
		if(temp.x>=0 && temp.y<=height && temp.x<=width && temp.y>=0)
		{
			drawPixel(temp, image, width, max);
		}

		//setPixel(xm+x, ym-y);  III. Quadrant
		temp.x = center.x+pixel.x;
		temp.y = center.y-pixel.y;
		temp.color=center.color;
		if(temp.x>=0 && temp.y<=height && temp.x<=width && temp.y>=0)
		{
			drawPixel(temp, image, width, max);
		}

		//setPixel(xm+y, ym+x);   IV. Quadrant
		temp.x = center.x+pixel.y;
		temp.y = center.y+pixel.x;
		temp.color=center.color;
		if(temp.x>=0 && temp.y<=height && temp.x<=width && temp.y>=0)
		{
			drawPixel(temp, image, width, max);
		}

		radius = err;
		if (radius <= pixel.y) err += ++(pixel.y)*2+1;           //e_xy+e_y < 0
		if (radius > pixel.x || err > pixel.y) err += ++(pixel.x)*2+1; //e_xy+e_x > 0 or no 2nd y-step

	} while (pixel.x < 0);
}

void starField(int image[], long int maxb, RGBTriplet color, int prop)
{

	int i;
	int reduction=0;
	for (i=0; i<maxb ; i++)
	{
		if(!(rand()%prop))
		{
			reduction=(rand()%128)+50;
			color.r=color.r-reduction;
			color.g=color.g-reduction;
			color.b=color.b-reduction;
			drawPixelIndex(i, image, color, maxb);
		}
	}
}

//Function doesn't work now have to find a way to make color going blank whatever the color you choose
void beamOfLight(Pixel start, Pixel end, int heightBeam, int image[], long int width, long int maxb, int speed)
{
	int i;

	//Anti-"CoreDump"!
	if(heightBeam<2)
	{
		return;
	}

	//Sets the color incrementation period
	RGBTriplet stepcolor;
	stepcolor.r=(255-start.color.r)/(heightBeam/2);
	stepcolor.g=(255-start.color.g)/(heightBeam/2);
	stepcolor.b=(255-start.color.b)/(heightBeam/2);

	//Initializes the symetrical pixels
	Pixel pixelSymStart;
	Pixel pixelSymEnd;
	pixelSymStart.x=start.x;
	pixelSymEnd.x=end.x;
	pixelSymStart.y=(start.y)+(heightBeam);
	pixelSymEnd.y=(end.y)+(heightBeam);
	pixelSymStart.color=start.color;
	pixelSymEnd.color=end.color;

	for(i=0; i<=(heightBeam/2); i++)
	{
		drawLine(start, end, image, width, maxb);
		drawLine(pixelSymStart, pixelSymEnd, image, width, maxb);
		start.y++;
		end.y++;
		pixelSymStart.y--;
		pixelSymEnd.y--;
		start.color.r+=stepcolor.r;
		start.color.g+=stepcolor.g;
		start.color.b+=stepcolor.b;
		pixelSymStart.color.r+=stepcolor.r;
		pixelSymStart.color.g+=stepcolor.g;
		pixelSymStart.color.b+=stepcolor.b;
	}
}
/*
void movingToCorner(char image[], long int max, RGBTriplet color, RGBTriplet colorBG, long int height, long int width)
{
	//Initialisations
	long int widthTemp, heightTemp;
	Pixel pixel;
	pixel.color.r=color.r;
	pixel.color.g=color.g;
	pixel.color.b=color.b;

	//Going to the middle from the top
	for(heightTemp=0; heightTemp<=height/2; heightTemp++)
	{
		for(widthTemp=0; widthTemp<=width; widthTemp++)
		{
			//If the pixel found is the good color
			if(image[(widthTemp+(heightTemp*width))]==color.b && image[(widthTemp+(heightTemp*width))+1]==color.g && image[(widthTemp+(heightTemp*width))+2]==color.b)
			{
				//Suppressing the old pixel
				pixel.x=widthTemp;
				pixel.y=heightTemp;
				pixel.color=colorBG;
				drawPixel(pixel, image, width, max);

				pixel.color.r=color.r;
				pixel.color.g=color.g;
				pixel.color.b=color.b;

				//Creating a new pixel at the good position
				if(widthTemp<=(width/2))
				{
					pixel.x-=1;
					pixel.y-=1;
					drawPixel(pixel, image, width, max);
				}
				else if(widthTemp>(width/2))
				{
					pixel.x+=1;
					pixel.y-=1;
					drawPixel(pixel, image, width, max);
				}
			}
		}
	}
	//Going to the middle from the bottom
	for (heightTemp=height; heightTemp>height/2; heightTemp--)
	{
		for(widthTemp=0; widthTemp<=width; widthTemp++)
		{
			//If the pixel found is the good color
			if(image[(widthTemp+(heightTemp*width))]==color.b && image[(widthTemp+(heightTemp*width))]==color.g && image[(widthTemp+(heightTemp*width))]==color.r)
			{
				//Suppressing the old pixel
				pixel.x=widthTemp;
				pixel.y=heightTemp;
				pixel.color=colorBG;
				drawPixel(pixel, image, width, max);
				pixel.color=color;

				//Creating a new pixel at the good position
				if(widthTemp>(width/2))
				{
					pixel.x=widthTemp+1;
					pixel.y=heightTemp+1;
					drawPixel(pixel, image, width, max);
				}
				else if(widthTemp<(width/2))
				{
					pixel.x=widthTemp-1;
					pixel.y=heightTemp+1;
					drawPixel(pixel, image, width, max);
				}
			}
		}
	}
}

void movingAllToCorner(int *image, int max, int colorBG, int height, int width)
{
	//Initialisations
	int widthTemp, heightTemp, colorTmp;
	Pixel pixel;
	pixel.color=0;

	//Going to the middle from the top
	for(heightTemp=0; heightTemp<=height/2; heightTemp++)
	{
		for(widthTemp=0; widthTemp<=width; widthTemp++)
		{
			//Getting the color of the old pixel
			colorTmp=image[(heightTemp*width)+widthTemp];
			//Suppressing the old pixel
			pixel.x=widthTemp;
			pixel.y=heightTemp;
			pixel.color=colorBG;
			drawPixel(pixel);
			//Creating a new pixel at the good position
			pixel.color=colorTmp;
			if(widthTemp<=(width/2))
			{
				pixel.x-=1;
				pixel.y-=1;
				drawPixel(pixel);
			}
			else if(widthTemp>(width/2))
			{
				pixel.x+=1;
				pixel.y-=1;
				drawPixel(pixel);
			}
		}
	}
	//Going to the middle from the bottom
	for (heightTemp=height; heightTemp>height/2; heightTemp--)
	{
		for(widthTemp=0; widthTemp<=width; widthTemp++)
		{
			//Getting the color of the old pixel
			colorTmp=image[(heightTemp*width)+widthTemp];
			//Suppressing the old pixel
			pixel.x=widthTemp;
			pixel.y=heightTemp;
			pixel.color=colorBG;
			drawPixel(pixel);
			pixel.color=colorTmp;

			//Creating a new pixel at the good position
			if(widthTemp>(width/2))
			{
				pixel.x=widthTemp+1;
				pixel.y=heightTemp+1;
				drawPixel(pixel);
			}
			else if(widthTemp<(width/2))
			{
				pixel.x=widthTemp-1;
				pixel.y=heightTemp+1;
				drawPixel(pixel);
			}
		}
	}
}
*/
/*
int getToRightX(long int val, long int lenght, long int width, long int offset)
{
	long int ytemp=0;
	long int finalval;
	while(val>=lenght)
	{
		val=val-lenght;
		ytemp++;
	}
	finalval=(ytemp*(width))+val+offset;
	return finalval;
}

void applyTransform(int transArray[], char image1[], char image2[], long int width, long int height, Pixel start, int lenght)
{
	long int x, y, offset, val;
	offset=((start.y)*width+((start.x)*4));
	for (y=0; y<lenght; y++)
	{
		for (x=0; x<lenght; x++)
		{
			val=transArray[((y*lenght)+x)];
			val=getToRightX(val, lenght, width, offset);
			image1[offset+((y*width)+(x*4))]=image2[val];
		}
	}
}

void lens(int radius, int magFact, int *image1, int *image2, int max, int width, int height, Pixel start)
{
	int x, y, x2, y2, temp, temp2, a, b;
	int s=((radius*radius)-(magFact*magFact));
	replaceImage(image2, image1, max);
	int lensTrans[((radius*2)*(radius*2))+1];
	for(x=0; x<((radius*2)*(radius*2))+1; x++)
	{
		lensTrans[x]=0;
	}
	for (y=-radius; y<=0; y++)
	{
		y2=y*y;
		temp=(y+radius)*(radius*2);
		temp2=(-y+radius)*(radius*2);
		for (x=-radius; x<=0; x++)
		{
			x2=x*x;
			if (x2+y2>=s)
			{
				a=x;
				b=y;
			}
			else
			{
				double z=sqrt((radius*radius)-x2-y2);
				a=(int)(x*(magFact/z));
				b=(int)(y*(magFact/z));
			}
			lensTrans[temp2+x-radius]=((-b + radius) * (radius*2) - (-a + radius)); //bottom left
			lensTrans[(temp2+(-x+radius))-(radius*2)]=((-b+radius)*(radius*2)+(-a+radius))-(radius*2); //bottom right
			lensTrans[(y+radius)*(radius*2)+(x+radius)]=(b+radius)*(radius*2)+(a+radius); // top left
			lensTrans[(temp-(x+radius))+(radius*2)]=(b+radius)*(radius*2)-(a+radius)+(radius*2); //top right
		}
	}
	applyTransform(lensTrans, image1, image2, width, height, start, radius*2);
}

void applyPlaneTransform (int mLUT[],int *image1, int *image2, int width, int height)
{
	int pixelcount, offset, u, v, adjustBright, r, g, b, color, timeShift;
	for (timeShift= 0; timeShift<10000; timeShift++)
	{
		for (pixelcount=0; pixelcount<(width*height); pixelcount++)
		{
			offset=(pixelcount << 1)+pixelcount;
			u=mLUT[offset]+timeShift;
			v=mLUT[offset+1]+timeShift;
			adjustBright=mLUT[offset+2];
			color=image2[(width*v & (height-1))+(u & (width-1))];
			if (adjustBright!=0)
			{
				invertRGB(color, &r, &g, &b);
				r+=adjustBright;
				if (r<0)
					r=0;
				if (r>255)
					r=255;
				g+=adjustBright;
				if (g<0)
					g=0;
				if (g>255)
					g=255;
				b+=adjustBright;
				if (b<0)
					b=0;
				if (b>255)
					b=255;
				color=colorRGB(r,g,b);
			}
			image1[pixelcount]=color;
		}
		if(timeShift%5==0)
			mini_update(image1);
	}
}

void planeTransform (int height, int width, int *image1, int *image2, int mode)
{
	int k=0, j, i;
	double u,v,bright=0, y, x, d, a, r;
	int mLUT[((height*width)*3)+1];
	for (j=0; j<height; j++)
	{
		y= -1.0 + 2.0*((double)j/((double)height));
		for (i=0; i<width; i++)
		{
			x=-1.0+2.0*((double)i/((double)width));
			d=sqrt(x*x+y*y);
			a=atan2(x,y);
			r=d;
			switch (mode)
			{
				case 1: //steroegraphic projection
				u=(cos(a))/d;
				v=(sin(a))/d;
				bright=-10*(2/((6*r)+(3*x)));
				break;

				case 2: //The amazing rotating tunnel of wonder!
				v=2/(6*r+3*x);
				u=(a*3)/M_PI;
				bright=15*(-v);
				break;

				case 3: //Spiral effect
				v=sin(a+cos(3*r))/(pow(r,0.2));
				u=cos(a+cos(3*r))/(pow(r,0.2));
				bright=1;
				break;

				case 4: //Wavy in star shape
				v=(-0.4/r)+(0.1*sin(8*a));
 		    	u=0.5+(0.5*a/M_PI);
   		    	bright=0;
   		    	break;

				case 5: //Hyper space travel
				u=(0.02*y+0.03)*cos(a*3)/r;
				v=(0.02*y+0.03)*sin(a*3)/r;
				bright=0;
				break;

				case 6: //5 points distord
				u = 1/(r+0.5+0.5*sin(5*a));
				v = a*3/M_PI;
				bright = 0;
				break;

				case 7: //accumulating layer
				u = 0.1*x/(0.11+r*0.5);
				v = 0.1*y/(0.11+r*0.5);
				bright=0;
				break;

				case 8: //circle spreading
				u = 0.5*(a)/M_PI;
				v = sin(2*r);
				bright = 0;
				break;

				case 9:
				v = pow(r,0.1);
				u = (1*a/M_PI)+r;
				bright=0;
				break;
			}

			mLUT[k++]=((int)(width*u))&(width-1);
			mLUT[k++]=((int)(height*v))&(height-1);
			mLUT[k++]=((int)bright);
		}
	}
	applyPlaneTransform (mLUT, image1, image2, width, height);
}*/
/*
void initGradientPalette(uint palette[256], RGBTriplet startColor, RGBTriplet endColor)
{
	int i;
	double n;
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	for(i = 0 ; i < 256 ; i++)
	{
		n = (double)i / (double)255;
		red = (double)startColor.r * (1.0 - n) + (double)endColor.r * n;
		green = (double)startColor.g * (1.0 - n) + (double)endColor.g * n;
		blue = (double)startColor.b * (1.0 - n) + (double)endColor.b * n;
		palette[i] = (red<<16 | green<<8 | blue);
	}
}

void drawFire(int fbp[], int *image, uint palette[256], int height, int width, uint timer)
{
	int i, j;
	uint average;
	uint loop = timer;
	unsigned int index = 0;

	for (i = 0 ; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			image[j * width + i] = 0;
		}
	}

	while(loop)
	{
		for(i = 0 ; i < width ; i+= width / 500)
			image[(height - 1) * width + i] = rand() % 2 ? 0 : 255;
		for (i = 0 ; i < width-1 ; i++)
		{
			for (j = height-2 ; j > 1 ; --j)
			{
				if(i > 0 || i < width-1)
				{
					average = (image[(j + 1) * width + (i - 1)] + image[(j + 1) * width + i] + image[(j + 1) * width + (i + 1)]) / 3;
					if(average > 0)
						image[j * width + i] = average - 1;
					else
						image[j * width + i] = 0;
				}
				else
					image[j * width + i] = 0;

			}
		}

		for (i = 0 ; i < width; ++i)
		{
			for (j = 0; j < height; ++j)
			{
				index = j * width + (i * 4);

				//fbp[index] = palette[image[j * width + i]];

			}
		}
		usleep(10);
		loop--;
	}

}


/*
void drawLulz(int *image1, int *image2, uint palette[256], int max, int height, int width)
{
	int i, j;
	int average;
	int loop = height;

	while(loop != 0)
	{
		for(i = 0 ; i < width-1 ; i++)
			image1[(height - 1) * width + i] = rand() % 2 ? 0 : 255;

		for (i = 0 ; i < width-1 ; ++i)
		{
			for (j = 1 ; j < (height - 1) ; ++j)
			{
				average = (image1[(j - 1) * width + ((i - 1) % width)] + image1[(j - 1) * width + (i % width)] + image1[(j - 1) * width + ((i + 1) % width)]) / 3;
				image2[j * width + i] = palette[(average - 1) % 256];
			}
		}

		mini_update(image2);
		image1 = image2;

		loop--;
	}

}

void drawPlasma(int *image1, int *image2, uint palette[256], int max, int height, int width, uint timer)
{
	int i, j;
	uint loop = timer;

	for (i = 0 ; i < width; ++i)
	{
		for (j = 0; j < height; ++j)
		{
			image1[j * width + i] = colorRGB(0, 0, 0);
		}
	}

	while(loop)
	{
		for (i = 0 ; i < width; ++i)
		{
			for (j = 0; j < height; ++j)
			{
				image1[j * width + i] = ((int)((sin(i) + 1) * 8192)) % 256;
			}
		}

		for (i = 0 ; i < width; ++i)
		{
			for (j = 0; j < height; ++j)
			{
				image2[j * width + i] = palette[image1[j * width + i]];
			}
		}

		usleep(10);
		mini_update(image2);
		loop--;
	}
}
*/
