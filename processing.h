#ifndef LIBPRO
#define LIBPRO

typedef unsigned int uint;
//Define the 3 charateritics of a pixel
typedef struct Pixel{
	int x;
	int y;
	int color;
}Pixel;

typedef struct RGBTriplet
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
}RGBTriplet;

void open_ppm(uint image[], char* file);
//Change the state of one pixel in the image table
void drawPixel(Pixel pixel, int *image, int width, int max);
//Change the state of one pixel in the image table with the given index
void drawPixelIndex(int index, int color, int max, int *image);
//Fill the image with the given color
void fillImage(int *image, int color, int width, int max);
//Replace color1 with color2 on the entire image
void replaceColor(int color1, int color2, int *image, int max);
//Draw a line in the given image
void drawLine(Pixel start, Pixel end, int *image, int width, int max);
//Draw a circle 
//Other way to draw a circle but malfunctioning...
void drawCircle2(Pixel center, int radius, int *image, int width, int max);
void drawCircle(const Pixel center, int radius, int *image, int height, int width);
//Draw a starfiel on the given image with the given color
void starField(int *image, int max, int color);
//Create a beam of light with the given color and given position with a blank fading inside
void beamOfLight(Pixel start, Pixel end, int heightBeam, int *image, int width, int max, int speed);
//Move all the point of the given color to the edges
void movingToCorner(int *image, int max, int color, int colorBG, int height, int width);
//Creates a gradient color palette
void initGradientPalette(uint palette[256], RGBTriplet startColor, RGBTriplet endColor);
//Fire effect
void drawFire(int *image, int *image2, uint palette[256], int max, int height, int width);

#endif