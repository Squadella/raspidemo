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
	int image1[MAXSIZE], image2[MAXSIZE], width, height;
	width = 722;
	height = 541;
	int i=0, num=10, j, lol=0, temp;
	int max=(width-1)*(height-1);
	int *p_image = image1;
	FILE* out;

	out=fopen("out.txt", "w");
	init_image(image1);
	//init_image(image2);
	//image[height/3*width+width/4] = colorRGB(255, 255, 255);
	mini_open("foobar", width, height);
	printf("press ESC to quit\n");

	while(i<num)
	{
		/* The mini_update fonction is heavy in ressources trying to put it one in a while and not too often
		Trying to understand the behavior of mini_update in loops*/
		for(j=0; j<height; j++)
		{
			temp=i;
			for(lol=0; lol<width; lol+=temp*(width-1)/num)
			{
				fprintf(out,"%d, %d\n", lol, temp);
				drawPixel(lol, j, colorRGB(255, 0, 0), p_image, width, max);
				temp++;
			}
			mini_update(p_image);
		}
		starField(p_image, max);
		//drawLine(i*(width-1)/num, 0, i*(width-1)/num, height-1, colorRGB(i*(width-1)/num,i*(width-1)/num,i*(width-1)/num), image, width, max);	
		
		i++;
	}
	


	while(0==0)
		mini_update(p_image);

	fclose(out);
	mini_close();
	return 0;
}
