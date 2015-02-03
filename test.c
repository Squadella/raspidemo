//Our libraries
#include "libgmini.h"
#include "processing.h"
#include "alphabet.h"

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

int main()
{
	//Initialisation of all the variables
	srand(time(NULL));
	int width, height/*, nbrLine, space*/, i, j, resize;
	//Dynamic allocation of the variables to avoid segfault
	int *image1 = malloc(sizeof(int)*MAXSIZE);
	int *image2 = malloc(sizeof(int)*MAXSIZE);
	//width = 800;
	//height = 600;
	width = 800;
	height = 600;
	int max=(width)*(height);
	init_image(image1);
	init_image(image2);

	//uint palette[256];
	Pixel pixel3;

	//Opening the image window
	mini_open("foobar", width, height);
	printf("press ESC to quit\n");

	//Starting drawing!
	/*
	//The word demo is asceding the windows and become smaller
	pixel3.x=100;
	pixel3.y=height;
	resize=10;
	fillImage(image2, colorRGB(0, 0, 0), width, max);
	for(i=1; i<height; i++)
	{
		for(j=resize*6; j<width; j+=71*resize)
		{
			pixel3.color=colorRGB(i,i/3,i/2);
			drawAlphabet('D', resize, image1, pixel3, width, max);
			pixel3.x+=10*resize;
			drawAlphabet('E', resize, image1, pixel3, width, max);
			pixel3.x+=10*resize;
			drawAlphabet('M', resize, image1, pixel3, width, max);
			pixel3.x+=10*resize;
			drawAlphabet('O', resize, image1, pixel3, width, max);
			pixel3.x=j;
		}
		pixel3.y--;
		if (i%(height/10)==0)
		{
			resize--;
		}
		mini_update(image1);
		usleep(100);
		replaceImage(image1, image2, max);
	}
	*/

	open_ppm(image1, "p");
	//open_ppm(image2, "p");
	fillImage(image2, colorRGB(0, 0, 255), width, max);
	starField(image2, max, colorRGB(255, 255, 255), 10);
	pixel3.x=200;
	pixel3.y=200;
	pixel3.color=colorRGB(255, 255, 255);
	mini_update(image2);
	printf("lol\n");
	sleep(2);
	//drawAlphabet('D', 10, image1, pixel3, width, max, 2);
	mini_update(image1);
	planeTransform (height, width, image1, image2, 9);
	//lens(100, 45, image1, image2, max, width, height, pixel3);
	mini_update(image1);
	printf("fin trait\n");

	while(0==0)
		mini_update(image1);

	free(image1);
	//drawCircle(Pixel center, int radius, int *image, int height, int width)
	return 0;
}