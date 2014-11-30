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
	init_image(image);
	image[height/3*width+width/4] = colorRGB(255, 255, 255);
	mini_open("foobar", width, height);
	printf("press ESC to quit\n");
	open_ppm(image);
	while(0==0)
		mini_update(image);
	mini_close();
	return 0;
}
