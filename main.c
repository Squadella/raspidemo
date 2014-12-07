//Our libraries!
#include "libgmini.h"
#include "processing.h"

//Other libraries
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 1600*1200


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
	int width, height, nbrLine, space, x, y, y1;
	//Dynamic allocation of the variables for avoiding segfault
	int *image2 = malloc(sizeof(int)*MAXSIZE);
	int *image1 = malloc(sizeof(int)*MAXSIZE);
	width = 1600;
	height = 1200;
	int max=(width)*(height);
	int *p_image = image1;
	init_image(image1);
	init_image(image2);
	Pixel pixel, pixel1;

	//Debug file
	FILE* out;
	out=fopen("out.txt", "w");

	//Opening the image window
	mini_open("foobar", width, height);
	printf("press ESC to quit\n");
	pixel.color=colorRGB(255, 0, 0);

	// Drawing descending lines with Breseham
	nbrLine=10;
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
			drawLine(pixel, pixel1, image2, width, max);
		}
		changeImage(image1, image2);
		y1=y;
	}

	//Drawing a blank star field
	//starField(image1, max, colorRGB(255, 255, 255));
	pixel.x=0;
	pixel.y=100;
	pixel.color=colorRGB(255, 0, 0);
	pixel1.x=1000;
	pixel1.y=100;
	pixel1.color=colorRGB(255, 0, 0);

	beamOfLight(pixel, pixel1, 20, image1, width, max);


	//Keeping the window open
	while(0==0)
		mini_update(p_image);

	fclose(out);
	mini_close();
	return 0;
}
