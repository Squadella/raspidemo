#include "libgmini.h"
#include "processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

//Open a ppm file and print it in the window
void open_ppm(uint image[], char* file)
{

	// initialising the file
	FILE *img;
	int returnTest;
	/*const char fileName[25];
	printf("Enter the name of the file you want to open:");
	scanf("loup.ppm", fileName);*/
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
	uint red=0;
	uint blue=0;
	uint green=0;
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
		if(fscanf(img, "%u", &green)!=1)
		{
			printf("Reading red error at index %u!\n", i);
			fclose(img);
			return;
		}
		if(fscanf(img, "%u", &red)!=1)
		{
			printf("Reading green error at index %u!\n",i);
			fclose(img);
			return;
		}
		if(fscanf(img, "%u", &blue)!=1)
		{
			printf("Reading blue error at index %u!\n", i);
			fclose(img);
			return;
		}
		image[i]=colorRGB(red,blue,green);
	}
	fclose(img);
}

// Draw a pixel with the given color
void drawPixel(Pixel pixel, int *image, int width, int max)
{
	int index=(pixel.y)*width+(pixel.x);
	if (index>=max || index<0)
	{
		return;
	}
	*(image+index)=(pixel.color);
}

void drawPixelIndex(int index, int color, int max, int *image)
{
	if(index>=max)
	{
		return;
	}
	*(image+index)=color;
}

void fillImage(int *image, int color, int width, int max)
{
	int i;
	for(i=0; i<max; i++)
	{
		drawPixelIndex(i, color, max, image);
	}
}

void replaceColor(int color1, int color2, int *image, int max)
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

void drawLine(Pixel start, Pixel end, int *image, int width, int max)
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

void drawCircle2(Pixel center, int radius, int *image, int width, int max)
{
	//Initialisations
	Pixel start, end;
	start.color=center.color;
	end.color=center.color;
	int y, x;
	
	for (y = -radius; y < radius; y++)
	{
		x = (int)(sqrt((float)(radius*radius - y * y)));
		start.x=center.x-x;
		end.x=center.x-x;
		start.y=center.y+y;
		end.y=center.y-y;
		printf("%d, %d, %d, %d\n", start.x, start.y, end.x, end.y);
		drawLine(start, end, image, width, max);
		start.x=center.x+x;
		end.x=center.x+x;
		drawLine(start, end, image, width, max);
	}
}

void drawCircle(const Pixel center, int radius, int *image, int height, int width)
{
	Pixel pixel, temp;
	int max=height*width;
	int err = 2-2*radius;
	pixel.x = -radius;
	pixel.y = 0;
	/*if(radius*2>height || radius*2>width)
	{
		return;
	}*/
	do
	{
		//setPixel(xm-x, ym+y); I. Quadrant
		temp.x = center.x-pixel.x;
		temp.y = center.y+pixel.y;
		temp.color=center.color;
		//if (temp.x>=0)
		//{
			drawPixel(temp, image, width, max);
		//}

		//setPixel(xm-y, ym-x);   II. Quadrant
		temp.x = center.x-pixel.y;
		temp.y = center.y-pixel.x;
		temp.color=center.color;
	//	if(temp.x>=0)
	//	{
		//	if(temp.y>=0)
		//	{
				drawPixel(temp, image, width, max);
		//	}
		//}

		//setPixel(xm+x, ym-y);  III. Quadrant
		temp.x = center.x+pixel.x;
		temp.y = center.y-pixel.y;
		temp.color=center.color;
		//if(temp.y>=0)
		//{
			drawPixel(temp, image, width, max);
		//}

		//setPixel(xm+y, ym+x);   IV. Quadrant
		temp.x = center.x+pixel.y;
		temp.y = center.y+pixel.x;
		temp.color=center.color;

		radius = err;
		if (radius <= pixel.y) err += ++(pixel.y)*2+1;           //e_xy+e_y < 0
		if (radius > pixel.x || err > pixel.y) err += ++(pixel.x)*2+1; //e_xy+e_x > 0 or no 2nd y-step

	} while (pixel.x < 0);
}

void starField(int *image, int max, int color)
{

	int i;
	for (i=0; i<max ;i++)
	{
		if(!(rand()%100))
		{
			*(image+i)=color;
		}
	}
}

//Function doesn't work now have to find a way to make color going blank whatever the color you choose
void beamOfLight(Pixel start, Pixel end, int heightBeam, int *image, int width, int max, int speed)
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
	usleep(speed);
	mini_update(image);
}

void movingToCorner(int *image, int max, int color, int colorBG, int height, int width)
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
		red = (double)startColor.red * (1.0 - n) + (double)endColor.red * n;
		green = (double)startColor.green * (1.0 - n) + (double)endColor.green * n;
		blue = (double)startColor.blue * (1.0 - n) + (double)endColor.blue * n;
		palette[i] = (red<<16 | green<<8 | blue);
	}
}

void drawFire(int *image1, int *image2, uint palette[256], int max, int height, int width)
{
	int i, j;
	int average;
	int loop = height;

	while(loop != 0)
	{
		for(i = 0 ; i < width ; i++)
		{
			for(j = 600 ; j >= 590 ; j--)
				image1[j * width + i] = palette[225 - (rand() % 30)];
		}

		for(i = 0 ; i < width ; i += 60 - (rand() % 50))
		{
			if(i - 1 < width)
			{
				image1[595 * width + i] = colorRGB(255, 255, 255);
				image1[595 * width + i + 1] = colorRGB(255, 255, 255);
				image1[595 * width + i - 1] = colorRGB(255, 255, 255);
				image1[594 * width + i] = colorRGB(255, 255, 255);
				image1[594 * width + i + 1] = colorRGB(255, 255, 255);
				image1[594 * width + i - 1] = colorRGB(255, 255, 255);
				image1[596 * width + i] = colorRGB(255, 255, 255);
				image1[596 * width + i + 1] = colorRGB(255, 255, 255);
				image1[596 * width + i - 1] = colorRGB(255, 255, 255);
			}
		}

		for(i = 0 ; i < width ; i++)
		{
			for(j = 1 ; j < height ; j++)
			{
				average = (image1[(j - 1) * width + i] + image1[j * width + (i - 1) % width] + image1[j * width + (i + 1) % width]) / 3;
				if(average != 0)
					image2[(j - 1) * width + i] = (average - 1);
				else
					image2[(j - 1) * width + i] = 0;
			}
		}
		mini_update(image2);
		image1 = image2;

		//loop--;
	}
	
}
