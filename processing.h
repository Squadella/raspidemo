#ifndef LIBPRO
#define LIBPRO

typedef unsigned int uint;
//Define the 3 charateritics of a pixel

typedef struct RGBTriplet
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
}RGBTriplet;

typedef struct Pixel{
	int x;
	int y;
	RGBTriplet color;
}Pixel;

void open_ppm(char image[], char* file, int depth);
//Change the state of one pixel in the image table
void drawPixel(Pixel pixel, char fbp[], long int width, long int max);
//Change the state of one pixel in the image table with the given index
void drawPixelIndex(int index, char fbp[], RGBTriplet color, long int max);
//Fill the image with the given color
void fillImage(char fbp[], RGBTriplet color, int width, int max);
//Replace the printed image by another
void replaceImage(char image1[], char image2[], long int maxb);
//Fade to black
void fadeToBlack(char image[], long int maxb);
//Concatenate image2 into image1 by choosing a x or y
void catImage(int *image1, int *image2, int x, int y, int direction, int height, int width);
//Replace color1 with color2 on the entire image
void replaceColor(RGBTriplet color1, RGBTriplet color2, char image[], int maxb);
//Draw a line in the given image
void drawLine(Pixel start, Pixel end, char image[], long int width, long int maxb);
//Draw a circle
void drawCircle(const Pixel center, int radius, char image[], long int height, long int width);
//Draw a starfiel on the given image with the given color
void starField(char image[], long int maxb, RGBTriplet color, int prop);
//Create a beam of light with the given color and given position with a blank fading inside
void beamOfLight(Pixel start, Pixel end, int heightBeam, char image[], long int width, long int maxb, int speed);
//Move all the point of the given color to the edges
void movingToCorner(char image[], long int max, RGBTriplet color, RGBTriplet colorBG, long int height, long int width);
//Move all the point ignoring the color
void movingAllToCorner(int *image, int max, int colorBG, int height, int width);
//Create the good index for applying transform
int getToRightX(long int val, long int lenght, long int width, long int offset);
//Apply a trnasformation on image1 with the image2
void applyTransform(int transArray[], char image1[], char image2[], long int width, long int height, Pixel start, int lenght);
//Make the lens effect on the screen
void lens(int radius, int magFact, int *image1, int *image2, int max, int width, int height, Pixel start);
//Transform the given image
void planeTransform (int height, int width, int *image1, int *image2, int mode);
//Creates a gradient color palette
void initGradientPalette(uint palette[256], RGBTriplet startColor, RGBTriplet endColor);
//Fire effect
void drawFire(int *image1, int *image2, uint palette[256], int max, int height, int width, uint timer);

void drawLulz(int *image1, int *image2, uint palette[256], int max, int height, int width);

void drawPlasma(int *image1, int *image2, uint palette[256], int max, int height, int width, uint timer);
#endif
