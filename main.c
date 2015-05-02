//Our libraries
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
int *fbp = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
struct fb_bitfield fbinf;

int main()
{
	//Initialisation of all the variables
	long int lineSize, bufferSize, heightSize, maxi, height, width;
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
	lineSize=vinfo.xres*depth;
	heightSize=vinfo.yres*depth;
	bufferSize=lineSize*vinfo.yres/8;
	maxi=bufferSize/4;
	height=vinfo.yres;
	width=vinfo.xres;

	// map framebuffer to user memory
	fbp = (int*)mmap(NULL, bufferSize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	int *fbp2=malloc(bufferSize * sizeof(int));
	int *palette = malloc(sizeof(int)*256);
	open_ppm(palette, "fire2.ppm");
	if ((int)fbp == -1)
	{
		printf("Failed to mmap the framebuffer.\n");

		return(-1);
	}
	while(1)
	{
		//Initialisation for drawing
		Pixel pixel, pixel2, pixel3;
		RGBTriplet rgb1, rgb2;
		int color, color2;
		int i, j;
		uint pal[256];
		int random=(rand()%25) + 1;
		color=0;
		fillImage(fbp, color, lineSize, maxi);
		pixel.x=0;
		pixel.y=0;
		pixel.color=colorRGB(255, 255, 255);
		pixel2.x=300;
		pixel2.y=300;
		pixel2.color=colorRGB(0, 0, 0);
		color2=colorRGB(255, 255, 255);
		pixel3.x = 0;
		pixel3.y = 0;
		pixel3.color = 0;

		fillImage(fbp, color, lineSize, maxi);
		drawPalette(fbp, palette, maxi, height, width);
		sleep(10);
		drawPlasma(fbp2, fbp, palette, maxi, height, width, 1000);
		sleep(1);
		replaceColor(color, color2, fbp, maxi);
		sleep(2);
		open_ppm(fbp, "4");
		sleep(1);
		fadeToBlack(fbp, maxi);
		color=colorRGB(255, 255, 255);
		//fillImage(fbp, color, lineSize, maxi);
		//drawCircle(pixel2, 100, fbp, width, height, maxi);
		sleep(2);
		color=0;
		fillImage(fbp, color, lineSize, maxi);
		color=colorRGB(255,255,255);
		starField(fbp, maxi, color, 100);
		sleep(1);
		pixel.color=colorRGB(0,255,0);
		for(i=0; i<random; i++)
		{
			pixel.x = rand()%width;
			pixel.y = rand()%height;
			pixel.color = colorRGB(rand()%256, rand()%256, rand()%256);
			pixel2.x = rand()%width;
			pixel2.y = rand()%height;

			beamOfLight(pixel, pixel2, 42, fbp, width, maxi, 0);
			sleep(1);
		}
		sleep(2);
		rgb2.r = 0;
		rgb2.g = 0;
		rgb2.b = 255;

		rgb1.r = 222;
		rgb1.g = 112;
		rgb1.b = 15;
		initGradientPalette(pal, rgb1, rgb2);

		for(i = 0; i < width; i++)
		{
			for(j = 0; j < height; j++)
			{
				pixel3.x = i;
				pixel3.y = j;
				pixel3.color = pal[(i*j)%256];
				drawPixel(pixel3, fbp, width, maxi);
			}
			usleep(300);
		}
		sleep(2);

		replaceImage(fbp2, fbp, maxi);
		planeTransform (height, width, fbp, fbp2, 8, 256);
		color2=0;
		for(i=0; i<width/4; i++)
		movingAllToCorner(fbp, maxi, color2, height, width);
		open_ppm(fbp2,"diern.ppm");
		planeTransform (height, width, fbp, fbp2, 1, 256);
		fillImage(fbp2, color2, lineSize, maxi);
		starField(fbp2, maxi, color, 100);
		sleep(1);
		planeTransform (height, width, fbp, fbp2, 7, 256);


	}
	/*
	pixel.color=0;
	for(i=random; i>0; i--)
	{
	pixel.x=rand()%vinfo.xres;
	pixel.y=rand()%vinfo.yres;
	pixel2.x=rand()%vinfo.xres;
	pixel2.y=rand()%vinfo.yres;
	beamOfLight(pixel, pixel2, 30, fbp, lineSize, bufferSize, 0);
	sleep(1);
}
pixel.color=0;
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
