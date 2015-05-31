#ifndef LIBPRO
#define LIBPRO

typedef unsigned int uint;

///Define the 3 colors component of a pixel.
typedef struct RGBTriplet
{
	unsigned char r; /**<The red part of the pixel.*/
	unsigned char g; /**<The green part of the pixel.*/
	unsigned char b; /**<The blue part of the pixel.*/
}RGBTriplet;

///Define the position and the color of a pixel.
typedef struct Pixel{
	int x; /**<The abscissa of a point.*/
	int y; /**<The ordinate of a point.*/
	int color; /**<The color of a pixel concatened in a int.*/
}Pixel;

///Function for concatenate the three color of a pixel into
int colorRGB(int r/**<The red part of the pixel.*/,
			 int g/**<The green part of the pixel.*/,
			 int b/**<The blue part of the pixel.*/);

///Function for getting the 3 color components of a given color.
void invertRGB(int color, int *red, int *green, int *blue);
///Function for loading a .ppm file inside the framebuffer.
void open_ppm(int image[], char* file);
///Change the state of one pixel in the framebuffer.
void drawPixel(Pixel pixel, int *image, int width, long int max);
///Change the state of one pixel in the framebuffer with the given index.
void drawPixelIndex(int index, int color, long int max, int *image);
///Fill the framebuffer with the given color.
void fillImage(int *image, int color, int width, int max);
///Copy a image table into the framebuffer.
void replaceImage(int *image1, int *image2, long int max);
///Shift all the pixel inside the framebuffer to black.
void fadeToBlack(int image[], long int maxb);
///Concatenate image2 into image1 by choosing a x or y.
void catImage(int *image1, int *image2, int x, int y, int direction, int height, int width);
///Replace color1 with color2 on the entire framebuffer.
void replaceColor(int color1, int color2, int *image, long int max);
///Draw a line in the given image.
void drawLine(Pixel start, Pixel end, int *image, int width, int max);
///Draw a circle in the given image.
void drawCircle(const Pixel center, int radius, int *image, long int height, long int width, long int maxi);
///Draw a starfiel on the given image with the given color.
void starField(int *image, int max, int color, int prop);
///Create a beam of light with the given color and given position with a blank fading in the middle.
void beamOfLight(Pixel start, Pixel end, int heightBeam, int *image, int width, int max, int speed);
///Move all the point of the given color to the edges of the screen.
void movingToCorner(int *image, int max, int color, int colorBG, int height, int width);
///Move all the points ignoring the color.
void movingAllToCorner(int *image, int max, int colorBG, int height, int width);
///Make image2 appear in square in the middle of the screen.
void squareOpening(int image[], int image2[], int max, int width, int height, int *widthTemp, int *widthTemp2, int *heightTemp, int *heightTemp2);
///Create the good index for applying a transform matrix.
int getToRightX(int val, int lenght, int width, int offset);
///Genrate the image1 by transformating image2 with a transform matrix.
void applyTransform(int transArray[], int *image1, int *image2, int width, int height, Pixel start, int lenght);
///Apply a lens transform the image2 and put it in image1.
void lens(int radius, int magFact, int *image1, int *image2, int max, int width, int height, Pixel start);
///Apply a plane transform with a transform array, mLUT, to image2 and save it into image1.
void applyPlaneTransform (int mLUT[],int *image1, int *image2, int width, int height, int timer);
///Different sort of plane transform applied to image2 and saved in imag1 depending of the mode.
void planeTransform (int height, int width, int *image1, int *image2, int mode, int timer);
///Creates a gradient color palette.
void initGradientPalette(uint palette[256], RGBTriplet startColor, RGBTriplet endColor);
///Load fire effect into image1.
void drawFire(int *image1, int *image2, uint palette[256], int max, int height, int width, uint timer);
///Unknow effect, use with caution, there is HUGE memory leak with this function.
void drawLulz(int *image1, int *image2, uint palette[256], int max, int height, int width);
///Load plasma effect into image1.
void drawPlasma(int *image1, int *image2, int palette[], int max, int height, int width, int timer);
#endif
