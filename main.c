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

    int x, y, max, i;
	Pixel pixel1, pixel2;
    max=vinfo.xres*vinfo.yres*3;
    char *fbp2 = malloc(max*sizeof(char));
    char *palette = malloc((256*3)*sizeof(char));
	pixel1.x = 0;
	pixel1.y = 0;
	pixel2.x = vinfo.xres;
	pixel2.y = vinfo.yres;
	pixel1.color = colorRGB(255,0,0);
	pixel2.color = 1;

    fillImage(fbp, 0, vinfo.xres, max);
    drawLine(pixel1, pixel2, fbp, vinfo.xres, max);
    sleep(1);
    starField(fbp, max, colorRGB(255,255,255), 100);
    sleep(1);
    beamOfLight(pixel1, pixel2, 10, fbp, vinfo.xres, max, 1);
    sleep(1);
    starField(fbp, max, colorRGB(255,255,255), 200);
    planeTransform(vinfo.yres, vinfo.xres, fbp, fbp2, 7, 1000);
    movingAllToCorner(fbp, max, 0, vinfo.yres, vinfo.xres);

    pixel1.x=vinfo.xres/2;
    pixel1.y=vinfo.yres/2;
    sleep(1);
    drawCircle(pixel1, 10, fbp, vinfo.yres, vinfo.xres, max);
    sleep(1);

    open_ppm(fbp, "loup2.ppm");
    sleep(2);
    lens(10, 2, fbp, fbp2, max,  vinfo.xres, vinfo.yres, pixel1);
    sleep(2);
    planeTransform(vinfo.yres, vinfo.xres, fbp, fbp2, 3, 1000);
    sleep(2);

    open_ppm(palette, "toast.ppm");
    drawPalette(fbp, palette, max, vinfo.yres, vinfo.xres);
    sleep(2);
    drawPlasma(fbp, fbp2, palette, max, vinfo.yres, vinfo.xres, 300);
    planeTransform(vinfo.yres, vinfo.xres, fbp, fbp2, 8, 1000);

    drawFire(fbp, fbp2, palette, max, vinfo.yres, vinfo.xres, 300);

    sleep(5);

}

// application entry point
int main(int argc, char* argv[])
{

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
    vinfo.xres = 160;
    vinfo.yres = 120;
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
        sleep(5);
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
