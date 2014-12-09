//Our libraries!
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
		-do we keep a black image for reseting the windows?
		-do we do a function for fill a table in the wanted color? (je pense que ça peut être utile si on fait une fênètre qui change de couleur en mode arc en ciel)
		-implement the double buffering
		-creating PGM effects
*/

int main() {
	//Initialisation of all the variables
	srand(time(NULL));
	int width, height, nbrLine, space, x, y, y1 ;
	//Dynamic allocation of the variables for avoiding segfault
	int *image2 = malloc(sizeof(int)*MAXSIZE);
	int *image1 = malloc(sizeof(int)*MAXSIZE);
	width = 800;
	height = 600;
	int max=(width)*(height);
	int *p_image = image1;
	init_image(image1);
	init_image(image2);
	Pixel pixel, pixel1, pixel3;

	//Debug file
	/*FILE* out;
	out=fopen("out.txt", "w");*/

	//Opening the image window
	mini_open("foobar", width, height);
	printf("press ESC to quit\n");
	pixel.color=colorRGB(255, 0, 0);
	//int r, g, b, i;
	int i;

	// Drawing descending lines with Breseham
/*	nbrLine=10;
	space=width/nbrLine;
	y1=0;
	pixel1.color=colorRGB(255,0,0);
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

	//Drawing a blank star field
	starField(image1, max, colorRGB(255, 255, 255));
*/
	//Drawing a light beam
	pixel.x=0;
	pixel.y=rand()%height;
	pixel.color=colorRGB(0, 200, 0);
	pixel1.x=width;
	pixel1.y=(rand()%height)+1;
	pixel1.color=colorRGB(77, 210, 207);
	pixel3.x=width/2;
	pixel3.y=height/2;
	pixel3.color=colorRGB(255,0,0);
	drawCircle(pixel3, 120, image1, height, width);
	beamOfLight(pixel, pixel1, rand()%150, image1, width, max, 10000);
	mini_update(image1);
	sleep(1);
	/*
	for(i=0; i<256; i++)
	{
		pixel.x=0;
		pixel.y=rand()%(height);
		pixel1.x=width;
		pixel1.y=(rand()%(height))+1;
		fprintf(out, "pixel.x: %d,  pixel.y: %d, pixel1.x: %d, pixel1.y: %d\n", pixel.x, pixel.y, pixel1.x, pixel1.y);
		fillImage(image1, colorRGB(i,i/3,i/2), width, max);
		beamOfLight(pixel, pixel1, rand()%150, image1, width, max, 10000);
		mini_update(image1);
		usleep(100000);
	}*/

	fillImage(image1, colorRGB(255,255,255), width, max);
	starField(image1, max, colorRGB(255,255,255));
	drawPixel(pixel, image1, width, max);
	mini_update(image1);
	//sleep(10);
	for (i=0; i<100; i++)
	{
		movingStarField(image1, max, colorRGB(255,255,255), colorRGB(0,0,0), height, width);
		mini_update(image1);
		usleep(10000);
	}

	//Keeping the window open
	while(0==0)
		mini_update(p_image);

	//fclose(out);
	mini_close();
	return 0;
}
