#include "processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

int colorRGB(int r, int g, int b) {
	return( r<<16 | g<<8 | b );
}

void invertRGB(int color, int *red, int *green, int *blue)
{
	*red=color/65536;
	*green=(color%65536)/256;
	*blue=color % 256;
}

//Open a ppm file and print it in the window
void open_ppm(char image[], char* file)
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
	uint green=0;
	uint red=0;
	uint blue=0;
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
	size=width*height*3;
	//writing the table with the new values
	for (i=0;i<size; i+=3)
	{
		if(fscanf(img, "%u", &green)!=1)
		{
			printf("Reading red error at index %u!\n", i);
			fclose(img);
			return;
		}

		if(fscanf(img, "%u", &red)!=1)
		{
			printf("Reading red error at index %u!\n", i);
			fclose(img);
			return;
		}

		if(fscanf(img, "%u", &blue)!=1)
		{
			printf("Reading red error at index %u!\n", i);
			fclose(img);
			return;
		}

		memcpy(image+i, (char*)&red, 1);
		memcpy(image+i+1, (char*)&blue, 1);
		memcpy(image+i+2, (char*)&green, 1);
	}
	fclose(img);
}

// Draw a pixel with the given color

void drawPixel(Pixel pixel, char *image, int width, long int max)
{
	int index=((pixel.y) * width + (pixel.x))*3;
	if (index>=max || index<0)
	{
		return;
	}
	int r, g, b;

	invertRGB(pixel.color, &r, &g, &b);

	*((char*)(image + index)) = b;
	*((char*)(image + index + 1)) = g;
	*((char*)(image + index + 2)) = r;
}

void drawPixelIndex(int index, int color, long int max, char *image)
{
	if(index>=max)
	{
		return;
	}
	int r, g, b;

	invertRGB(color, &r, &g, &b);

	*((char*)(image + index)) = b;
	*((char*)(image + index + 1)) = g;
	*((char*)(image + index + 2)) = r;
}

void fillImage(char *image, int color, int width, int max)
{
	int i;
	for(i=0; i<max; i+=3)
	{
		drawPixelIndex(i, color, max, image);
	}
}

void replaceImage(char *image1, char *image2, long int max)
{
	int i;
	for(i=0; i<max; i++)
	{
		image1[i]=image2[i];
	}
}

void replaceColor(int color1, int color2, char *image, long int max)
{
	int index;
	for(index=0; index<max; index++)
	{
		if(*(image+index)==color1)
		{
			drawPixelIndex(index, color2, max, image);
		}
	}
}

void catImage(char *image1, char *image2, int x, int y, int direction, int height, int width)
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

void fadeToBlack(int fbp[], long int maxi)
{
	int i = 0, j = 0;
	int r, g, b;

	for(j = 256; j >=0; j-=4)
	{
		for(i = 0; i < maxi; i++)
		{
			invertRGB(fbp[i], &r, &g, &b);

			if(r > 0)
			{
				r -= 4;
				if(r < 0)
				r = 0;
			}

			if(g > 0)
			{
				g -= 4;
				if(g < 0)
				g = 0;
			}

			if(b > 0)
			{
				b -= 4;
				if(b < 0)
				b = 0;
			}

			fbp[i] = colorRGB(r, g, b);
		}
	}
}
/*
void catImageColor(char *image1, char *image2, int color, int height, int width)
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
void drawLine(Pixel start, Pixel end, char *image, int width, int max)
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
		drawPixel(start, image, width, max);
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

void drawCircle(const Pixel center, int radius, char *image, long int height, long int width, long int max)
{
	Pixel pixel, temp;
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
		//setPixel(xm-y, ym-x); II. Quadrant
		temp.x = center.x-pixel.y;
		temp.y = center.y-pixel.x;
		temp.color=center.color;
		if(temp.x>=0 && temp.y<=height && temp.x<=width && temp.y>=0)
		{
			drawPixel(temp, image, width, max);
		}
		//setPixel(xm+x, ym-y); III. Quadrant
		temp.x = center.x+pixel.x;
		temp.y = center.y-pixel.y;
		temp.color=center.color;
		if(temp.x>=0 && temp.y<=height && temp.x<=width && temp.y>=0)
		{
			drawPixel(temp, image, width, max);
		}
		//setPixel(xm+y, ym+x); IV. Quadrant
		temp.x = center.x+pixel.y;
		temp.y = center.y+pixel.x;
		temp.color=center.color;
		if(temp.x>=0 && temp.y<=height && temp.x<=width && temp.y>=0)
		{
			drawPixel(temp, image, width, max);
		}
		radius = err;
		if (radius <= pixel.y) err += ++(pixel.y)*2+1; //e_xy+e_y < 0
		if (radius > pixel.x || err > pixel.y) err += ++(pixel.x)*2+1; //e_xy+e_x > 0 or no 2nd y-step
	} while (pixel.x < 0);
}

void starField(char *image, int max, int color, int prop)
{
	int i;
	int reduction=0;
	for (i=0; i<max ;i+=3)
	{
		if(!(rand()%prop))
		{
			reduction=(rand()%128)+50;
			drawPixelIndex(i, color-colorRGB(reduction, reduction, reduction), max, image);
		}
	}
}

//Function doesn't work now have to find a way to make color going blank whatever the color you choose
void beamOfLight(Pixel start, Pixel end, int heightBeam, char *image, int width, int max, int speed)
{
	int i, r=0, g=0, b=0;
	//Anti-"CoreDump"!
	if(heightBeam<2)
	{
		return;
	}
	//Sets the color incrementation period
	invertRGB(start.color, &r, &g, &b);
	int stepcolor=colorRGB((255-r)/(heightBeam/2), (255-g)/(heightBeam/2), (255-b)/(heightBeam/2));
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
		drawLine(start, end, image, width, max);
		drawLine(pixelSymStart, pixelSymEnd, image, width, max);
		start.y++;
		end.y++;
		pixelSymStart.y--;
		pixelSymEnd.y--;
		start.color+=stepcolor;
		pixelSymStart.color+=stepcolor;
	}
}

void movingToCorner(char *image, int max, int color, int colorBG, int height, int width)
{
	//Initialisations
	int widthTemp, heightTemp;
	Pixel pixel;
	pixel.color=color;
	//Going to the middle from the top
	for(heightTemp=0; heightTemp<=height/2; heightTemp++)
	{
		for(widthTemp=0; widthTemp<=width; widthTemp++)
		{
			//If the pixel found is the good color
			if(*(image+(widthTemp+(heightTemp*width)))==color)
			{
				//Suppressing the old pixel
				pixel.x=widthTemp;
				pixel.y=heightTemp;
				pixel.color=colorBG;
				drawPixel(pixel, image, width, max);
				pixel.color=color;
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
			if(*(image+(widthTemp+(heightTemp*width)))==color)
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

void movingAllToCorner(char *image, int max, int colorBG, int height, int width)
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
			drawPixel(pixel, image, width, max);
			//Creating a new pixel at the good position
			pixel.color=colorTmp;
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
		usleep(8000);
	}
	//Going to the middle from the bottom
	for (heightTemp=height; heightTemp>height/2; heightTemp--)
	{
		for(widthTemp=0 ; widthTemp<=width; widthTemp++)
		{
			//Getting the color of the old pixel
			colorTmp=image[(heightTemp*width)+widthTemp];
			//Suppressing the old pixel
			pixel.x=widthTemp;
			pixel.y=heightTemp;
			pixel.color=colorBG;
			drawPixel(pixel, image, width, max);
			pixel.color=colorTmp;
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
		usleep(8000);
	}
}

int getToRightX(int val, int lenght, int width, int offset)
{
	int ytemp=0;
	int finalval;
	while(val>=lenght)
	{
		val=val-lenght;
		ytemp++;
	}
	finalval=(((ytemp*(width))+val)*3)+offset;
	return finalval;
}

void applyTransform(int transArray[], char *image1, char *image2, int width, int height, Pixel start, int lenght)
{
	int x, y, offset, val;
	offset=((start.y)*width+start.x)*3;
	for (y=0; y<lenght; y++)
	{
		for (x=0; x<lenght; x++)
		{
			val=transArray[((y*lenght)+x)];
			val=getToRightX(val, lenght, width, offset);
			image1[offset+(((y*width)+x)*3)]=image2[val];
			image1[offset+(((y*width)+x)*3)+1]=image2[val+1];
			image1[offset+(((y*width)+x)*3)+2]=image2[val+2];
		}
	}
}

void lens(int radius, int magFact, char *image1, char *image2, int max, int width, int height, Pixel start)
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

void applyPlaneTransform (int mLUT[], char *image1, char *image2, int width, int height, int time)
{
	int pixelcount, offset, u, v, adjustBright, r, g, b, color, timeShift;
	for (timeShift= 0; timeShift<time; timeShift++)
	{
		for (pixelcount=0; pixelcount<(width*height); pixelcount++)
		{
			offset=(pixelcount << 1)+pixelcount;
			u=mLUT[offset]+timeShift;
			v=mLUT[offset+1]+timeShift;
			adjustBright=mLUT[offset+2];
			b=image2[(width*(v & (height-1)))+(u & (width-1))];
			g=image2[(width*(v & (height-1)))+(u & (width-1))+1];
			r=image2[(width*(v & (height-1)))+(u & (width-1))+2];
			if (adjustBright!=0)
			{
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
			}
			image1[pixelcount]=b;
			image1[pixelcount+1]=g;
			image1[pixelcount+2]=r;
		}
	}
}

void planeTransform (int height, int width, char *image1, char *image2, int mode, int time)
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
	applyPlaneTransform (mLUT, image1, image2, width, height, time);
}

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

void drawFire(char *image1, char *image2, char *palette, int max, int height, int width, uint timer)
{
	int i, j;
	uint average;
	uint loop = timer;
	for (i = 0 ; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			image1[j * width + i] = colorRGB(0, 0, 0);
		}
	}
	while(loop != 0)
	{
		for(i = 0 ; i < width ; i+= width / 500)
		image1[(height - 1) * width + i] = rand() % 2 ? 0 : 255;
		for (i = 0 ; i < width-1 ; i++)
		{
			for (j = height-2 ; j > 1 ; --j)
			{
				if(i > 0 || i < width-1)
				{
					average = (image1[(j + 1) * width + (i - 1)] + image1[(j + 1) * width + i] + image1[(j + 1) * width + (i + 1)]) / 3;
					if(average > 0)
					image1[j * width + i] = average - 1;
					else
					image1[j * width + i] = 0;
				}
				else
				image1[j * width + i] = 0;
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
		loop--;
	}
}

void savePalette(int image[], int palette[], int max, int height, int width)
{
	int i, j;
	FILE *img;
	img=fopen("diern", "w");
	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			fprintf(img,"%d", palette[(i*width+j)%256]);
		}
	}
	fclose(img);
}


void drawPalette(char image[], char palette[], int max, int height, int width)
{
	int i, j;
	int height3=height*3;
	int width3=width*3;
	for(i=0; i<height3; i++)
	{
		for(j=0; j<width3; j++)
		{
			image[i*width+j]=palette[(i*width+j)%(256*3)];
		}
	}
}

void drawPlasma(char *image1, char *image2, char palette[], int max, int height, int width, int timer)
{
	int i, j;
	int loop = timer;
	int width3=width*3;
	fillImage(image1, 0, width, max);
	while(loop)
	{
		for (i = 0 ; i < width3; i++)
		{
			for (j = 0; j < height; j++)
			{
				image1[j * width3 + i] = abs((int)(64 +(loop + 63 * cos( i/(31*(j+1)) )*cos(j*i+42)))% (256*3));
			}
		}
		for (i = 0 ; i < width3; i++)
		{
			for (j = 0; j < height; j++)
			{
				image2[j * width3 + i] = palette[image1[j * width3 + i]];
			}
		}
		loop--;
	}
}

void randRectangle(Pixel pixel1, Pixel pixel2, Pixel pixel3, Pixel pixel4, char *fbp, int width, int max)
{
	drawLine(pixel1, pixel2, fbp, width, max);
	drawLine(pixel2, pixel3, fbp, width, max);
	drawLine(pixel3, pixel4, fbp, width, max);
	drawLine(pixel4, pixel1, fbp, width, max);
	rand()%2 ? pixel1.x++ : pixel1.x--;
	rand()%2 ? pixel2.x++ : pixel2.x--;
	rand()%2 ? pixel3.x++ : pixel3.x--;
	rand()%2 ? pixel4.x++ : pixel4.x--;
	usleep(1000);
	fillImage(fbp, 0, width, max);
}
