//Our libraries
#include "libgmini.h"
#include "processing.h"

//Other libraries
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 1000*1000


void init_image(int *image) 
{
	int i;
	for(i=0; i<MAXSIZE; i++)
		*(image+i) = colorRGB(0, 0, 0);
}

/*
Things to do and test:
-do we keep a black image to reset the window?
-implement double-buffering
-creating PGM effects*/

int main() {
	//Initialisation of all the variables
	srand(time(NULL));
	int width, height/*, nbrLine, space, i*/;
	//Dynamic allocation of the variables to avoid segfault
	int *image2 = malloc(sizeof(uint)*MAXSIZE);
	int *image1 = malloc(sizeof(uint)*MAXSIZE);
	width = 800;
	height = 600;
	int max=(width)*(height);
	init_image(image1);
	init_image(image2);
	uint palette[256];
	//Pixel pixel, pixel1, pixel3;

	//Debug file
	/*FILE* out;
	out=fopen("out.txt", "w");*/

	//Opening the image window
	mini_open("foobar", width, height);
	printf("press ESC to quit\n");
	//pixel.color=colorRGB(0, 2, 255);
	//int r, g, b, i;

	/*RGBTriplet start = {0, 0, 0}, end = {255, 0, 0};
	initGradientPalette(palette, start, end);*/
	open_ppm(palette, "fire2.ppm");
	
	drawPlasma(image1, image2, palette, max, height, width, 1000);
/*
	// Drawing descending lines with Bresenham
	nbrLine=10;
	space=width/nbrLine;
	y1=0;
	pixel1.color=colorRGB(0,2,255);
	for (y=0; y<height; y+=3)
	{
		for (x=0; x<width; x+=space)
		{
			pixel.x=x;
			pixel.y=y1;
			pixel1.y=y;
			pixel1.x=x;
			drawLine(pixel, pixel1, image1, width, max);
		}
		//changeImage(image1, image2);
		mini_update(p_image);
		y1=y;
	}
*/
	//Drawing a blank star field
	//starField(image1, max, colorRGB(255, 255, 255));

	//Drawing a light beam
	/*pixel.x=100;
	pixel.y=rand()%height;
	pixel.color=colorRGB(0, 200, 0);
	pixel1.x=width-100;
	pixel1.y=(rand()%height)+1;
	pixel1.color=colorRGB(77, 210, 207);
	pixel3.x=width/2;
	pixel3.y=height/2;
	pixel3.color=colorRGB(255,0,0);
	drawCircle(pixel3, 120, image1, height, width);
	beamOfLight(pixel, pixel1, rand()%150, image1, width, max, 10000);
	mini_update(image1);
	sleep(1);*/
	
	//Random laser on a changing color background
	/*
	for(i=0; i<256; i++)
	{
		pixel.x=0;
		pixel.y=rand()%(height);
		pixel1.x=width;
		pixel1.y=(rand()%(height))+1;
		fillImage(image1, colorRGB(i,i/3,i/2), width, max);
		beamOfLight(pixel, pixel1, rand()%150, image1, width, max, 10000);
		mini_update(image1);
	usleep(100000);
	}
	*/

	//Rainbow background
	/*int red=255, green=0, blue=0;
	for (space=0; space<10; space++)
	{
		for(i=0; i<255; i++)
		{
			blue++;
			//printf("%d %d %d\n", red, green, blue);
			fillImage(image1, colorRGB(red,green,blue), width, max);
			mini_update(image1);
			usleep(1000);
		}
		for(i=255; i>0; i--)
		{
			red--;
			//printf("%d %d %d\n", red, green, blue);
			mini_update(image1);
			fillImage(image1, colorRGB(red,green,blue), width, max);
			usleep(1000);
		}
		for(i=0; i<255; i++)
		{
			green++;
			//printf("%d %d %d\n", red, green, blue);
			mini_update(image1);
			fillImage(image1, colorRGB(red,green,blue), width, max);
			usleep(1000);
		}
		for(i=255; i>0; i--)
		{
			blue--;
			//printf("%d %d %d\n", red, green, blue);
			fillImage(image1, colorRGB(red,green,blue), width, max);
			mini_update(image1);
			usleep(1000);
		}
		for(i=0; i<255; i++)
		{
			red++;
			//printf("%d %d %d\n", red, green, blue);
			fillImage(image1, colorRGB(red,green,blue), width, max);
			mini_update(image1);
			usleep(1000);
		}
		for(i=255; i>0; i--)
		{
			green--;
			//printf("%d %d %d\n", red, green, blue);
			fillImage(image1, colorRGB(red,green,blue), width, max);
			mini_update(image1);
			usleep(1000);
		}
	}*/
	/*
	fillImage(image1, colorRGB(0,0,0), width, max);
	starField(image1, max, colorRGB(0,0,0));
	drawPixel(pixel, image1, width, max);
	mini_update(image1);
	//sleep(10);
	for (i=0; i<100; i++)
	{
		movingToCorner(image1, max, colorRGB(0,0,0), colorRGB(i,i/3,i/2), height, width);
		mini_update(image1);
		usleep(10000);
	}

	replaceColor(colorRGB(0,0,0), colorRGB(0,255,0), image1, max);*/
	//Keeping the window open
	while(0==0)
		mini_update(image1);

	free(image1);
	free(image2);
	//fclose(out);
	mini_close();
	return 0;
}