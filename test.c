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
	int width, height;
	//Dynamic allocation of the variables to avoid segfault
	int *image1 = malloc(sizeof(int)*MAXSIZE);
	int *image2 = malloc(sizeof(int)*MAXSIZE);
	width = 800;
	height = 600;
	int max=(width)*(height);
	init_image(image1);
	init_image(image2);

	uint palette[256];

	//Opening the image window
	mini_open("foobar", width, height);
	printf("press ESC to quit\n");

	open_ppm(palette, "fire.ppm");
	drawFire(image1, image2, palette, max, height, width, 2000);

	while(0==0)
		mini_update(image1);

	free(image1);
	//drawCircle(Pixel center, int radius, int *image, int height, int width)
	return 0;
}