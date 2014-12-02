#include "libgmini.h"
#include "libgmini.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	*(image+index)=color;
}

void drawLine(Pixel start, Pixel end, int image[], int width, int max)
{
	int dx = abs((end.x)-(start.x);
	int sx;
	if((start.x)<(end.x)))
		sx=1;
	else
		sx=-1;

	int dy = -abs((end.y)-(start.y);
	int sy;
	if((start.y)<(end.y))
		sy=1;
	else
		sy=-1;

	int err = dx+dy;
	int e2=0;
	while(1)
	{
		drawPixel(pixel, image, width, max);
		if(x0==x1 && y0==y1)
			break;
		e2=2*err;
		if(e2>=dy)
		{
			err=err+dy;
			x0=x0+sx;
		}
		if(e2<=dx)
		{
			err=err+dx;
			y0=y0+sy;
		}
	}
}

void starField(int image[], int max, int color)
{

	int i;
	for (i=0; i<max ;i++)
	{
		if(!(rand()%100))
		{
			image[i]=color;
		}
	}
};