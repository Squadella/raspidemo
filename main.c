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
char *fbp = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;

// helper function for drawing - no more need to go mess with
// the main function when just want to change what to draw...
void draw() {

    int x, y, max, i, lenghtRectangle, heightRectangle, random;
	Pixel pixel1, pixel2, pixel3, pixel4, pixel5, pixel6, pixel7, pixel8, pixel9, pixel10, pixel11, pixel12, pixel13, pixel14, pixel15, pixel16;
    max=vinfo.xres*vinfo.yres*3;
    char *fbp2 = malloc(max*sizeof(char));
    char *palette = malloc((256*3)*sizeof(char));
    lenghtRectangle=(rand()%128)+32;
    heightRectangle=(rand()%216)+24;

	pixel1.x = rand()%160;
	pixel1.y = rand()%120;
	pixel2.x = pixel1.x+lenghtRectangle;
	pixel2.y = pixel1.y;
    pixel3.x = pixel2.x;
    pixel3.y = pixel2.y+heightRectangle;
    pixel4.x = pixel1.x;
    pixel4.y = pixel1.y+heightRectangle;

    pixel5.x = rand()%160;
    pixel5.y = rand()%120;
    pixel6.x = rand()%160;
    pixel6.y = rand()%120;
    pixel7.x = rand()%160;
    pixel7.y = rand()%120;
    pixel8.x = rand()%160;
    pixel8.y = rand()%120;
    pixel9.x = rand()%160;
    pixel9.y = rand()%120;
    pixel10.x = rand()%160;
    pixel10.y = rand()%120;
    pixel11.x = rand()%160;
    pixel11.y = rand()%120;
    pixel12.x = rand()%160;
    pixel12.y = rand()%120;
    pixel13.x = rand()%160;
    pixel13.y = rand()%120;
    pixel14.x = rand()%160;
    pixel14.y = rand()%120;
    pixel15.x = rand()%160;
    pixel15.y = rand()%120;
    pixel16.x = rand()%160;
    pixel16.y = rand()%120;

	pixel1.color = colorRGB(34,139,34);
	pixel2.color = colorRGB(34,139,34);
    pixel3.color = colorRGB(34,139,34);
    pixel4.color = colorRGB(34,139,34);
    pixel5.color = rand()%colorRGB(255,255,255);
    pixel6.color = rand()%colorRGB(255,255,255);
    pixel7.color = rand()%colorRGB(255,255,255);
    pixel8.color = rand()%colorRGB(255,255,255);
    pixel9.color = rand()%colorRGB(255,255,255);
    pixel10.color = rand()%colorRGB(255,255,255);
    pixel11.color = rand()%colorRGB(255,255,255);
    pixel12.color = rand()%colorRGB(255,255,255);
    pixel13.color = rand()%colorRGB(255,255,255);
    pixel14.color = rand()%colorRGB(255,255,255);
    pixel15.color = rand()%colorRGB(255,255,255);
    pixel16.color = rand()%colorRGB(255,255,255);

    fillImage(fbp, 0, vinfo.xres, max);
    random=rand()%1000+1000;
    for(i=0; i<random; i++)
    {
        randRectangle(&pixel1, &pixel2, &pixel3, &pixel4, fbp, vinfo.xres, max);
        randRectangle(&pixel5, &pixel6, &pixel7, &pixel8, fbp, vinfo.xres, max);
        randRectangle(&pixel9, &pixel10, &pixel11, &pixel12, fbp, vinfo.xres, max);
        randRectangle(&pixel13, &pixel14, &pixel15, &pixel16, fbp, vinfo.xres, max);
    }
    sleep(1);
    starField(fbp, max, colorRGB(255,255,255), 50);
    sleep(1);
    pixel1.x=rand()%160;
    pixel1.x=rand()%120;
    pixel2.x=(rand()%160)+160;
    pixel2.y=(rand()%120)+120;
    beamOfLight(pixel1, pixel2, 10, fbp, vinfo.xres, max, 1);
    sleep(1);
    movingAllToCorner(fbp, max, 0, vinfo.yres, vinfo.xres);

    pixel1.x=vinfo.xres/2;
    pixel1.y=vinfo.yres/2;
    sleep(1);
    pixel1.color = colorRGB(34,139,34);
    random=10000;
    for(i=0; i<random; i++)
    {
        pixel1.x=rand()%320;
        pixel1.y=rand()%240;
        drawCircle(pixel1, rand()%120, fbp, vinfo.yres, vinfo.xres, max);
        pixel1.color=rand()%colorRGB(255,255,255);
        usleep(1000);
    }
    replaceImage(fbp2, fbp, max);
    pixel1.y=0;
    pixel1.x=0;
    pixel2.x=0;
    pixel2.y=vinfo.yres;
    for(i=0; i<vinfo.xres; i+=2)
    {
        pixel1.x+=2;
        pixel2.x=pixel1.x;
        drawLine(pixel1, pixel2, fbp2, vinfo.xres, max);
    }
    pixel1.x=0;
    pixel1.y=0;
    pixel2.y=0;
    pixel2.x=vinfo.xres;
    for(i=0; i<vinfo.xres; i+=2)
    {
        pixel1.y+=2;
        pixel2.y=pixel1.y;
        drawLine(pixel1, pixel2, fbp2, vinfo.xres, max);
    }

    planeTransform(vinfo.yres, vinfo.xres, fbp, fbp2, 6, 500);
    sleep(1);

    open_ppm(fbp, "loup2.ppm");
    sleep(2);
    lens(100, 2, fbp, fbp2, max,  vinfo.xres, vinfo.yres, pixel1);
    sleep(2);
    fadeToBlack(fbp, max);
    sleep(2);
    planeTransform(vinfo.yres, vinfo.xres, fbp, fbp2, 3, 500);
    planeTransform(vinfo.yres, vinfo.xres, fbp, fbp2, 7, 500);
    planeTransform(vinfo.yres, vinfo.xres, fbp, fbp2, 7, 500);
    planeTransform(vinfo.yres, vinfo.xres, fbp, fbp2, 5, 500);
    planeTransform(vinfo.yres, vinfo.xres, fbp, fbp2, 4, 500);
    sleep(2);

    open_ppm(palette, "toast.ppm");
    drawPalette(fbp, palette, max, vinfo.yres, vinfo.xres);
    drawPalette(fbp2, palette, max, vinfo.yres, vinfo.xres);
    sleep(2);
    drawPlasma(fbp, fbp2, palette, max, vinfo.yres, vinfo.xres, 300);
    planeTransform(vinfo.yres, vinfo.xres, fbp, fbp2, 8, 1000);

    sleep(5);

}

// application entry point
int main(int argc, char* argv[])
{
    srand(time(NULL));
    int fbfd = 0;
    struct fb_var_screeninfo orig_vinfo;
    long int screensize = 0;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        printf("Error: cannot open framebuffer device.\n");
        return(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
        printf("Error reading variable information.\n");
    }
    printf("Original %dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    // Store for reset (copy vinfo to vinfo_orig)
    memcpy(&orig_vinfo, &vinfo, sizeof(struct fb_var_screeninfo));

    // Change variable info - force 8 bit and resolution
    vinfo.bits_per_pixel = 24;
    vinfo.xres = 320;
    vinfo.yres = 240;
    vinfo.xres_virtual = vinfo.xres;
    vinfo.yres_virtual = vinfo.yres;
    if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo)) {
        printf("Error setting variable information.\n");
    }

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)) {
        printf("Error reading fixed information.\n");
    }

    // map fb to user mem
    screensize = finfo.smem_len;
    fbp = (char*)mmap(0,
              screensize,
              PROT_READ | PROT_WRITE,
              MAP_SHARED,
              fbfd,
              0);

    if ((int)fbp == -1) {
        printf("Failed to mmap.\n");
    }
    else {
        // draw...
        draw();
    }

    // cleanup
    // unmap fb file from memory
    munmap(fbp, screensize);
    // reset the display mode
    if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &orig_vinfo)) {
        printf("Error re-setting variable information.\n");
    }
    // close fb file
    close(fbfd);

    //Reopening the framebuffer with other settings
    //Initialisation of all the variables
	long int lineSize, bufferSize, heightSize, maxi, height, width;

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
	if ((int)fbp == -1)
	{
		printf("Failed to mmap the framebuffer.\n");

		return(-1);
	}

    // cleanup
    // unmap fb file from memory
    munmap(fbp, screensize);
    // reset the display mode
    if (ioctl(fbfd, FBIOPUT_VSCREENINFO, &orig_vinfo)) {
        printf("Error re-setting variable information.\n");
    }

    // close fb file
    close(fbfd);

    return 0;
}
