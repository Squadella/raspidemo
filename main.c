//Our libraries
#include "libgmini.h"
#include "processing.h"
//#include "alphabet.h"

//Other libraries
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

// 'global' variables to store screen info
char *fbp = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
struct fb_bitfield fbinf;

int main()
{
	//Initialisation of all the variables
	long int lineSize, bufferSize, heightSize;
	int fbfd=0;
	srand(time(NULL));

	//Opening framebuffer
	fbfd=open("/dev/fb0", O_RDWR);
	if (!fbfd)
	{
		printf("Error: cannot open framebuffer device.\n");
		printf("Try to run the executable file with root privileges.\n");
		return(-1);
	}

	//Get fixed sreen information
	if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo))
	{
		printf("Error reading fixed information of the screen.\n");
		return(-1);
    }

    // Get variable screen information
	if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo))
	{
		printf("Error reading variable information.\n");
		return(-1);
	}

	//Calculate the size of the framebuffer
	int depth=vinfo.bits_per_pixel;
	lineSize=vinfo.xres*depth/8;
	heightSize=vinfo.yres*depth/8;
	bufferSize=lineSize*vinfo.yres;

	// map framebuffer to user memory
	fbp = (char*)mmap(NULL, bufferSize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	if ((int)fbp == -1)
	{
		printf("Failed to mmap the framebuffer.\n");

		return(-1);
	}
	while(1)
	{
		//Initialisation for drawing
		Pixel pixel, pixel2;
		RGBTriplet color, color2;
		int i;
		int random=rand()%25;
		color.r=0;
		color.g=0;
		color.b=0;
		fillImage(fbp, color, lineSize, bufferSize);
		pixel.x=0;
		pixel.y=0;
		pixel.color.r=0;
		pixel.color.g=0;
		pixel.color.b=0;
		pixel2.x=600;
		pixel2.y=400;
		pixel2.color.r=0;
		pixel2.color.g=0;
		pixel2.color.b=0;
		color.r=203;
		color.g=238;
		color.b=232;
		color2.r=255;
		color2.g=0;
		color2.b=255;

		fillImage(fbp, color, lineSize, bufferSize);
		sleep(1);
		replaceColor(color, color2, fbp, bufferSize);
		sleep(2);
		open_ppm(fbp, "loup2.ppm", depth);
		sleep(1);
		color.r=0;
		color.g=0;
		color.b=0;
		fillImage(fbp, color, lineSize, bufferSize);
		drawCircle(pixel2, 10, fbp, heightSize, lineSize);
		sleep(2);
		color.r=0;
		color.g=0;
		color.b=0;
		fillImage(fbp, color, lineSize, bufferSize);
		color.r=255;
		color.g=255;
		color.b=255;
		starField(fbp, bufferSize, color, 100);
		pixel.color.r=255;
		pixel.color.g=0;
		pixel.color.b=0;
		for(i=random; i>0; i--)
		{
			pixel.x=rand()%vinfo.xres;
			pixel.y=rand()%vinfo.yres;
			pixel2.x=rand()%vinfo.xres;
			pixel2.y=rand()%vinfo.yres;
			beamOfLight(pixel, pixel2, 30, fbp, lineSize, bufferSize, 0);
			sleep(1);
		}
		pixel.color.r=0;
		pixel.color.g=0;
		pixel.color.b=255;
		beamOfLight(pixel, pixel2, 30, fbp, lineSize, bufferSize, 0);
		sleep(2);
	}
	//movingToCorner(fbp, bufferSize, color, color2, heightSize, lineSize);
	//Dynamic allocation of the variables to avoid segfault
	/*
	int *imageTmp = malloc(sizeof(int)*MAXSIZE);
	uint *palette = malloc(sizeof(uint)*256);
	width = 800;
	height = 600;
	int max=(width)*(height);
	init_image(image1);
	init_image(image2);
	init_image(imageTmp);
	RGBTriplet start = {0, 0, 0}, end = {255, 0, 0};
	open_ppm(palette, "fire2.ppm");

	//Opening the image window
	mini_open("foobar", width, height);
	printf("press ESC to quit\n");

	//The intro of the demo, the word demo is displayed
	mini_update(image2);
	pixel3.x=100;
	pixel3.y=height;
	resize=10;
	pixel3.color=colorRGB(255, 255, 255);
	for(i=1; i<height-20; i++)
	{
		for(j=resize*6; j<width; j+=71*resize)
		{
			pixel3.color=colorRGB(0, 0, 255);
			drawAlphabet('D', resize, image1, pixel3, width, height, (i%10)+1);
			pixel3.x+=12*resize;
			drawAlphabet('E', resize, image1, pixel3, width, height, (i%10)+1);
			pixel3.x+=12*resize;
			drawAlphabet('M', resize, image1, pixel3, width, height, (i%10)+1);
			pixel3.x+=12*resize;
			drawAlphabet('O', resize, image1, pixel3, width, height, (i%10)+1);
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
	//Draw a bit of fire
	drawFire(image1, image2, palette, max, height, width, 500);

	//Emptying the image and drawing a starfield
	fillImage(image1, colorRGB(0, 0, 0), width, max);
	starField(image1, max, colorRGB(255, 255, 255), 200);
	mini_update(image1);
	sleep(1);

	//Moving the starfield into the corner
	for (i=0; i<width/2; i++)
	{
		movingAllToCorner(image1, max, colorRGB(0, 0, 0), height, width);
		usleep(1000);
		mini_update(image1);
	}


	//catImage(int *image1, int *image2, int x, int y, int direction, int height, int width);
	//Pixel pixel, pixel1, pixel3;

	//Debug file
	FILE* out;
	out=fopen("out.txt", "w");

	//drawPlasma(image1, image2, palette, max, height, width, 1000);

	// Drawing descending lines with Bresenham
	nbrLine=10;
	space=width/nbrLine;
	y1=0;
	pixel1.color=colorRGB(0,2,255);
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
		//changeImage(image1, image2);
		mini_update(p_image);
		y1=y;
	}
*/
	//Drawing a blank star field
	//starField(image1, max, colorRGB(255, 255, 255));

	//Drawing a light beam
	/*pixel.x=100;
	pixel.y=rand()%height;
	pixel.color=colorRGB(0, 200, 0);
	pixel1.x=width-100;
	pixel1.y=(rand()%height)+1;
	pixel1.color=colorRGB(77, 210, 207);
	pixel3.x=width/2;
	pixel3.y=height/2;
	pixel3.color=colorRGB(255,0,0);
	drawCircle(pixel3, 120, image1, height, width);
	beamOfLight(pixel, pixel1, rand()%150, image1, width, max, 10000);
	mini_update(image1);
	sleep(1);*/

	//Random laser on a changing color background
	/*
	for(i=0; i<256; i++)
	{
		pixel.x=0;
		pixel.y=rand()%(height);
		pixel1.x=width;
		pixel1.y=(rand()%(height))+1;
		fillImage(image1, colorRGB(i,i/3,i/2), width, max);
		beamOfLight(pixel, pixel1, rand()%150, image1, width, max, 10000);
		mini_update(image1);
	usleep(100000);
	}
	*/

	//Rainbow background
	/*int red=255, green=0, blue=0;
	for (space=0; space<10; space++)
	{
		for(i=0; i<255; i++)
		{
			blue++;
			//printf("%d %d %d\n", red, green, blue);
			fillImage(image1, colorRGB(red,green,blue), width, max);
			mini_update(image1);
			usleep(1000);
		}
		for(i=255; i>0; i--)
		{
			red--;
			//printf("%d %d %d\n", red, green, blue);
			mini_update(image1);
			fillImage(image1, colorRGB(red,green,blue), width, max);
			usleep(1000);
		}
		for(i=0; i<255; i++)
		{
			green++;
			//printf("%d %d %d\n", red, green, blue);
			mini_update(image1);
			fillImage(image1, colorRGB(red,green,blue), width, max);
			usleep(1000);
		}
		for(i=255; i>0; i--)
		{
			blue--;
			//printf("%d %d %d\n", red, green, blue);
			fillImage(image1, colorRGB(red,green,blue), width, max);
			mini_update(image1);
			usleep(1000);
		}
		for(i=0; i<255; i++)
		{
			red++;
			//printf("%d %d %d\n", red, green, blue);
			fillImage(image1, colorRGB(red,green,blue), width, max);
			mini_update(image1);
			usleep(1000);
		}
		for(i=255; i>0; i--)
		{
			green--;
			//printf("%d %d %d\n", red, green, blue);
			fillImage(image1, colorRGB(red,green,blue), width, max);
			mini_update(image1);
			usleep(1000);
		}
	}*/
	/*
	fillImage(image1, colorRGB(0,0,0), width, max);
	starField(image1, max, colorRGB(0,0,0));
	drawPixel(pixel, image1, width, max);
	mini_update(image1);
	//sleep(10);
	for (i=0; i<100; i++)
	{
		movingToCorner(image1, max, colorRGB(0,0,0), colorRGB(i,i/3,i/2), height, width);
		mini_update(image1);
		usleep(10000);
	}

	replaceColor(colorRGB(0,0,0), colorRGB(0,255,0), image1, max);*/
	//Keeping the window open
	//while(0==0)
	//	mini_update(image1);

	//free(image1);
	//free(image2);
	//free(palette);
	//fclose(out);
	//mini_close();
	return 0;
}