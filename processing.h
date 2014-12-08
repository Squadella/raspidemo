#ifndef LIBPRO
#define LIBPRO

typedef unsigned int uint;
//Define the 3 charateritics of a pixel
typedef struct Pixel{
	uint x;
	uint y;
	int color;
}Pixel;

//Open a .ppm image
void open_ppm(int *image);
//Change the state of one pixel in the image table
void drawPixel(Pixel pixel, int *image, uint width, uint max);
//Change the state of one pixel in the image table with the given index
void drawPixelIndex(uint index, int color, uint max, int *image);
//Draw a line in the given image
void drawLine(Pixel start, Pixel end, int *image, uint width, uint max);
//Draw a starfiel on the given image with the given color
void starField(int *image, uint max, int color);
//Draw a circle 
void drawCircle(Pixel center, uint radius, int *image, uint height, uint width);
//Fill the image with the given color
void fillImage(int *image, int color, uint width, uint max);
//Change the showed image
void changeImage(int *current, int *next);
//Create a beam of light with the given color and given position with a blank fading inside
void beamOfLight(Pixel start, Pixel end, uint heightBeam, int *image, uint width, uint max, uint speed);


#endif