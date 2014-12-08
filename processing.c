#include "libgmini.h"
#include "libgmini.h"
#include "processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//Open a ppm file and print it in the window
void open_ppm(int image[])
{

	// initialising the file
	FILE *img;
	int returnTest;
	/*const char fileName[25];
	printf("Enter the name of the file you want to open:");
	scanf("loup.ppm", fileName);*/
	img=fopen("loup.ppm", "r");

	if (img==NULL) //if the program is unable to open the fil exit the function
	{
		printf("Unable to open file!\n");
		return;
	}
	
	//If the file is opened
	unsigned int height=0;
	unsigned int width=0;
	unsigned int size=0;
	unsigned int i=0;
	unsigned int red=0;
	unsigned int blue=0;
	unsigned int green=0;
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
	if (index>=max)
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

void drawLine(Pixel start, Pixel end, int image[], int width, int max)
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

void drawCircle(Pixel center, int radius, int *image, int height, int width)
{
	Pixel pixel, temp;
	int max=height*width;
	int err = 2-2*radius;
	pixel.x = -radius;
	pixel.y = 0;
	if(radius*2>height || radius*2>width)
	{
		return;
	}
	do
	{
		//setPixel(xm-x, ym+y); I. Quadrant
		temp.x = center.x-pixel.x;
		temp.y = center.y+pixel.y;
		temp.color=center.color;
		drawPixel(temp, image, width, max);

		//setPixel(xm-y, ym-x);   II. Quadrant
		temp.x = center.x-pixel.y;
		temp.y = center.y-pixel.x;
		temp.color=center.color;
		drawPixel(temp, image, width, max);

		//setPixel(xm+x, ym-y);  III. Quadrant
		temp.x = center.x+pixel.x;
		temp.y = center.y-pixel.y;
		temp.color=center.color;
		drawPixel(temp, image, width, max);

		//setPixel(xm+y, ym+x);   IV. Quadrant
		temp.x = center.x+pixel.y;
		temp.y = center.y+pixel.x;
		temp.color=center.color;
		drawPixel(temp, image, width, max);

		radius = err;
		if (radius <= pixel.y) err += ++(pixel.y)*2+1;           //e_xy+e_y < 0
		if (radius > pixel.x || err > pixel.y) err += ++(pixel.x)*2+1; //e_xy+e_x > 0 or no 2nd y-step

	} while (pixel.x < 0);
}

void fillImage(int *image, int color, int width, int max)
{
	int i;
	for(i=0; i<max; i++)
	{
		drawPixelIndex(i, color, max, image);
	}
}

//Can't change adress with malloc have to find another way
/*void changeImage(int *current, int *next)
{
	int **temp=&current;
	&current=&next;
	&next=temp;
	mini_update(current);
}*/

//Function doesn't wok now have to find a way to make color going blank whatever the color you choose
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
/*
void movingStarField(int *image, int max, int color)
{
	//Initialisations
	int i;

	starField(image, max, color);

	for(i=0; i<=max; i++)
	{
		if(*(image+i)==color)
		{

		}
	}
}*/