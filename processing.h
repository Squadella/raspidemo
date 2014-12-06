#ifndef LIBPRO
#define LIBPRO

//Define the 3 carateritics of a pixel
typedef struct Pixel{
	int x;
	int y;
	int color;
}Pixel;

//Open a .ppm image
void open_ppm(int *image);
//Change the state of one pixel in the image table
void drawPixel(Pixel pixel, int *image, int width, int max);
//Draw a line in the given image
void drawLine(Pixel start, Pixel end, int *image, int width, int max);
//Draw a starfiel on the given image with the given color
void starField(int *image, int max, int color);
//Draw a circle 
void drawCircle(Pixel center, int radius, int *image, int width, int max);

#endif