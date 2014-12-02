// to compile: 
// $ gcc -Wall -lXext main.c


#include "libgmini.h"
#include "processing.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1600*1200


void init_image(int *image) {
	int i;

	for(i=0; i<MAXSIZE; i++)
		*(image+i) = colorRGB(0, 0, 0);
}

int main() {
	int width, height;
	int *image2 = malloc(sizeof(int)*MAXSIZE);
	int *image1 = malloc(sizeof(int)*MAXSIZE);
	width = 722;
	height = 541;
	int i=0, num=10, j, lol=0, temp;
	int max=(width-1)*(height-1);
	int *p_image = image1;
	FILE* out;

	out=fopen("out.txt", "w");
	init_image(image1);
	init_image(image2);
	//image[height/3*width+width/4] = colorRGB(255, 255, 255);
	mini_open("foobar", width, height);
	printf("press ESC to quit\n");

	while(i<num)
	{
		for(j=0; j<height; j++)
		{
			temp=i;
			for(lol=0; lol<width; lol+=temp*(width-1)/num)
			{
				fprintf(out,"%d, %d\n", lol, temp);
				drawPixel(lol, j, colorRGB(255, 0, 0), image1, width, max);
				temp++;
			}
			mini_update(image1);
		}
		starField(image1, max);
		//drawLine(i*(width-1)/num, 0, i*(width-1)/num, height-1, colorRGB(i*(width-1)/num,i*(width-1)/num,i*(width-1)/num), image, width, max);	
		
		i++;
	}
	


	while(0==0)
		mini_update(p_image);

	fclose(out);
	mini_close();
	return 0;
}
