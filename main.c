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
	int i=0, num=10, j, lol=0, temp;
	int max=(width-1)*(height-1);
	init_image(image);
	//image[height/3*width+width/4] = colorRGB(255, 255, 255);
	mini_open("foobar", width, height);
	printf("press ESC to quit\n");
	//open_ppm(image);
	while(i<num)
	{
		for(j=0; j<height; j++)
		{
			temp=i;
			for(lol=0; lol<width; lol+=temp*(width-1)/num)
			{
				drawPixel(lol, j, colorRGB(255, 0, 0), image, width, max);
				usleep(50);
				temp++;
			}
			
		}
		//starField(image, max);
		//drawLine(i*(width-1)/num, 0, i*(width-1)/num, height-1, colorRGB(i*(width-1)/num,i*(width-1)/num,i*(width-1)/num), image, width, max);	
		mini_update(image);
		i++;
	}
	


	while(0==0)
		mini_update(image);

	mini_close();
	return 0;
}
