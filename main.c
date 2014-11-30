// to compile: 
// $ gcc -Wall -lXext main.c


#include "libgmini.h"
#include "processing.h"

#include <stdio.h>

#define MAXSIZE 1600*1200


void init_image(int image[]) {
	int i;

	for(i=0; i<MAXSIZE; i++)
		image[i] = colorRGB(0, 0, 0);
}

int main() {
	int image[MAXSIZE], width, height;

	width = 722;
	height = 541;
	//int i;
	int max=width*height;
	init_image(image);
	image[height/3*width+width/4] = colorRGB(255, 255, 255);
	mini_open("foobar", width, height);
	printf("press ESC to quit\n");
	open_ppm(image);
	drawLine(50, 50, 1000, 2000, 0, image, width, max);
	while(0==0)
		mini_update(image);
	mini_close();
	return 0;
}
