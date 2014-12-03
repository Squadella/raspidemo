// to compile: 
// $ gcc -Wall -lXext main.c


#include "libgmini.h"
#include "processing.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAXSIZE 1600*1200


void init_image(int *image) {
	int i;

	for(i=0; i<MAXSIZE; i++)
		*(image+i) = colorRGB(0, 0, 0);
}

int main() {

	srand(time(NULL));
	
	int width, height;
	width = 1366;
	height = 768;
	int *image1 = malloc(sizeof(int)*MAXSIZE);
	int i=0, num = (height-1)/2;
	int max = (width-1)*(height-1);
	Pixel pixel;

	init_image(image1);
	mini_open("foobar", width, height);
	printf("press ESC to quit\n");

	pixel.x=(width-1)/2;
	pixel.y=(height-1)/2;

	for (i = 1; i < num; ++i)
	{
		pixel.color=colorRGB(i%256, (i^3)%256, (i^i)%256);
		drawCircle(pixel, i, image1, width, max);
		mini_update(image1);
	}

	while(0==0)
		mini_update(image1);

	free(image1);
	mini_close();
	return 0;
}
