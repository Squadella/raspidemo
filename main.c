// to compile: 
// $ gcc -Wall -lXext main.c
// test

#include "libgmini.h"
#include "processing.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 1600*1200


void init_image(int *image) {
	int i;

	for(i=0; i<MAXSIZE; i++)
		*(image+i) = colorRGB(0, 0, 0);
}

int main() {
	srand(time(NULL));
	int width, height, nbrLine, space, x, y, y1;
	int *image2 = malloc(sizeof(int)*MAXSIZE);
	int *image1 = malloc(sizeof(int)*MAXSIZE);
	width = 722;
	height = 541;
	//int i=0, num=10, j, lol=0, temp;
	int max=(width)*(height);
	int *p_image = image1;
	FILE* out;

	out=fopen("out.txt", "w");
	init_image(image1);
	init_image(image2);
	//image[height/3*width+width/4] = colorRGB(255, 255, 255);
	mini_open("foobar", width, height);
	printf("press ESC to quit\n");
	Pixel pixel, pixel1;
	pixel.color=colorRGB(255, 0, 0);

	/* 
	while(i<num)
	{
		//The mini_update fonction is heavy in ressources trying to put it one in a while and not too often
		//Trying to understand the behavior of mini_update in loops

		//Drawing descending lines methode 1
		for(j=0; j<height; j++)
		{
			temp=i;
			for(lol=0; lol<width; lol+=temp*(width-1)/num)
			{
				fprintf(out,"%d, %d\n", lol, temp);
				pixel.x=lol;
				pixel.y=j;
				drawPixel(pixel, image1, width, max);
				temp++;	
			}
			mini_update(image1);
		}
		starField(image1, max, colorRGB(255, 255, 255));
		//drawLine(i*(width-1)/num, 0, i*(width-1)/num, height-1, colorRGB(i*(width-1)/num,i*(width-1)/num,i*(width-1)/num), image, width, max);	
		i++;
	}*/


	// Drawing descending lines method 2 with Breseham
	// This method is more powerfull than the other
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
			drawLine(pixel, pixel1, image1, width, max);
		}
		mini_update(image1);
		y1=y;
	}
	starField(image1, max, colorRGB(255, 255, 255));

	/*for(i=0; i<num; i++)
	{
		starField(image1, max, colorRGB((i*42)%256, ((i*42)+64)%256, ((i*42)+128)%256));
		mini_update(image1);
	}*/

	while(0==0)
		mini_update(p_image);

	fclose(out);
	mini_close();
	return 0;
}
