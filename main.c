// to compile: 
// $ gcc -Wall -lXext main.c


#include "libgmini.h"
#include "processing.h"

#include <unistd.h>
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
	int i=0;
	int max=(width-1)*(height-1);
	init_image(image);
	//image[height/3*width+width/4] = colorRGB(255, 255, 255);
	mini_open("foobar", width, height);
	printf("press ESC to quit\n");
	//open_ppm(image);
	while(i<10)
	{
		starField(image, max);
	//drawLine((width-1)/2, 0, (width-1)/2, height-1, colorRGB(255,255,255), image, width, max);
	mini_update(image);
	sleep(1);
	i++;
		
	}
	


	while(0==0)
		mini_update(image);

	mini_close();
	return 0;
}
