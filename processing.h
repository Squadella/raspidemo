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
void invertRGB(int color/**<The color given by a pixel.*/,
	 		   int *red/**<The resulting red color after shiting the int.*/,
			   int *green/**<The resulting green color after shiting the int.*/,
			   int *blue/**<The resulting blue color after shiting the int.*/);

///Function for loading a .ppm file inside the framebuffer.
void open_ppm(char image[]/**<The array where the image will be saved.*/,
			  char* file/**<The name of the image file.*/);

///Change the state of one pixel in the framebuffer.
void drawPixel(Pixel pixel, char *image, int width, long int max);

///Change the state of one pixel in the framebuffer with the given index.
void drawPixelIndex(int index/**<The index in the array we want to change*/,
	 				int color/**<The color we want to use for the new pixel.*/,
					long int max/**<The max index of the image array.*/,
					char *image/**<The array where the programm will place the pixel.*/);

///Fill the image array with the given color.
void fillImage(char *image/**<The array where the programm will fill with the given color.*/,
			   int color/**<Color of the filling.*/,
			   int width/**<The width of the screen.*/,
			   int max/**<The max index of the image array.*/);

///Copy a image table into the framebuffer.
void replaceImage(char *image1/**<The current image.*/,
	 			  char *image2/**<The image we want to insert.*/,
				  long int max/**<The max index of the image array.*/);

///Shift all the pixel inside the framebuffer to black.
void fadeToBlack(int fbp[]/**<The current image.*/,
	 			 long int maxi/**<The max index of the image array.*/);

///Concatenate image2 into image1 by choosing a x or y.
void catImage(char *image1/**<The current image.*/,
	 		  char *image2/**<The image we want to insert.*/,
			  int x/**<Set the limit of the separation of the two in the x axis (ignored if set to -1).*/,
			  int y/**<Set the limit of the separation of the two in the y axis (ignored if set to -1).*/,
			  int direction/**<Set the delimitation the if y = -1 go to the rigth if true and if the x=-1 go up if false.*/,
			  int height/**<The height of the screen.*/,
			  int width/**<The width of the screen.*/);

///Replace color1 with color2 on the entire framebuffer.
void replaceColor(int color1/**<The color that will be replaced.*/,
	 			  int color2/**<The color to put in found areas.*/,
				  char *image/**<The current image.*/,
				  long int max/**<The max index of the image array.*/);

///Draw a line in the given image with Bresenham's algorithm.
void drawLine(Pixel start/**<The first pixel of the line.*/,
	 		  Pixel end/**<The last pixel of the line*/,
			  char *image/**<The current image.*/,
			  int width/**<The height of the screen.*/,
			  int max/**<The max index of the image array.*/);

///Draw a circle in the given image.
void drawCircle(const Pixel center/**<The center pixel of the circle.*/,
				int radius/**<The radius of the circle.*/,
				char *image/**<The current image.*/,
				long int height/**<The height of the screen.*/,
				long int width/**<The width of the screen.*/,
				long int maxi/**<The max index of the image array.*/);

///Draw a starfiel on the given image with the given color.
void starField(char *image/**<The image where the starfield will be drawn.*/,
			   int max/**<The max index of the image array.*/,
			   int color/**<The color of the stars.*/,
			   int prop/**<The chance of apparition of a star.*/);

///Create a beam of light with the given color and given position with a blank fading in the middle.
void beamOfLight(Pixel start/**<The start pixel of the middle of the beam.*/,
	 			 Pixel end/**<The end pixel of the middle of the beam.*/,
				 int heightBeam/**<The size of the beam in height.*/,
				 char *image/**<The image where the starfield will be drawn.*/,
				 int width/**<The width of the screen.*/,
				 int max/**<The max index of the image array.*/,
				 int speed/**<The spee of appariton of the beam.*/);

///Move all the point of the given color to the edges of the screen.
void movingToCorner(char *image/**<The current image.*/,
					int max/**<The max index of the image array.*/,
					int color/**<The color that will be moved.*/,
					int colorBG/**<The color of replacement when a piwel moves.*/,
					int height/**<The height of the screen.*/,
					int width/**<The width of the screen.*/);

///Move all the points ignoring the color.
void movingAllToCorner(char *image/**<The current image.*/,
					   int max/**<The max index of the image array.*/,
					   int colorBG/**<The color of replacement when a piwel moves.*/,
					   int height/**<The height of the screen.*/,
					   int width/**<The width of the screen.*/);

///Make image2 appear in square in the middle of the screen.
void squareOpening(int image[]/**<The current image.*/,
				   int image2[]/**<The image we want to print.*/,
				   int max/**<The max index of the image array.*/,
				   int width/**<The width of the screen.*/,
				   int height/**<The height of the screen.*/,
				   int *widthTemp/**<Temp values for calling function multiples times (set to 0 when called).*/,
				   int *widthTemp2/**<Temp values for calling function multiples times (set to 0 when called).*/,
				   int *heightTemp/**<Temp values for calling function multiples times (set to 0 when called).*/,
				   int *heightTemp2/**<Temp values for calling function multiples times (set to 0 when called).*/);

///Create the good index for applying a transform matrix.
int getToRightX(int val/**<The index value.*/,
	 			int lenght/**<The lenght of the transformation array.*/,
				int width/**<The width of the image*/,
				int offset/**<The offset for the start of the transform array in the image*/);

///Genrate the image1 by transformating image2 with a transform matrix.
void applyTransform(int transArray[]/**<The transform array.*/,
					char *image1/**<The current image.*/,
					char *image2/**<The source image.*/,
					int width/**<The width of the images.*/,
					int height/**<The height of the images.*/,
					Pixel start/**<The start pixel of the transform.*/,
					int lenght/**<The lenght of the rtansform.*/);

///Apply a lens transform the image2 and put it in image1.
void lens(int radius/**<The radius of the lens.*/,
		  int magFact/**<The magnifying factor.*/,
		  char *image1/**<The current image.*/,
		  char *image2/**<The source image.*/,
		  int max/**<The max index of the image array.*/,
		  int width/**<The width of the screen.*/,
		  int height/**<The height of the screen.*/,
		  Pixel start/**<The start pixel of the transform.*/);

///Applying a plane trasform with the given transformation array.
void applyPlaneTransform (int mLUT[]/**<The transformation array.*/,
	 					  char *image1/**<The current image.*/,
	 					  char *image2/**<The source image.*/,
						  int width/**<The width of the screen.*/,
						  int height/**<The height of the screen.*/,
	 					  int time/**<The duration of the effect.*/);

///Different sort of plane transform applied to image2 and saved in imag1 depending of the mode.
void planeTransform (int height/**<The height of the screen.*/,
					 int width/**<The width of the screen.*/,
					 char *image1/**<The displayed image.*/,
					 char *image2/**<The source image.*/,
					 int mode/**<The different type of plane transform can take nummber from 1 to 9.*/,
					 int time/**<The duration of the effect.*/);

///Creates a gradient color palette.
void initGradientPalette(uint palette[256]/**<The palette that will be created.*/,
	 					 RGBTriplet startColor/**<The R G B color of start.*/,
						 RGBTriplet endColor/**<The R G B color of end.*/);

///Fire effect loaded into image1.
void drawFire(char *image1/**<The displayed image.*/,
	 		  char *image2/**<A temp image.*/,
			  uint palette[256]/**<The palette for coloration of the pixels.*/,
			  int max/**<The max index of the image array.*/,
			  int height/**<The height of the screen.*/,
			  int width/**<The width of the screen.*/,
			  uint timer/**<The duration of the effect.*/);

///Unknow effect, use with caution, there is HUGE memory leak with this function.
void drawLulz(char *image1/**<The displayed image.*/,
	 		  char *image2/**<A temp image.*/,
			  uint palette[256]/**<The palette for coloration of the pixels.*/,
			  int max/**<The max index of the image array.*/,
			  int height/**<The height of the screen.*/,
			  int width/**<The width of the screen.*/);

///Save all the data of a palette in a file.
void savePalette(int image[]/**<The displayed image.*/,
	 			 int palette[]/**<The palette that will be saved.*/,
	 			 int max/**<The max index of the image array.*/,
				 int height/**<The height of the screen.*/,
				 int width/**<The width of the screen.*/);

///Put the palette multiple time in image.
void drawPalette(int image[]/**<The displayed image.*/,
	 			 int palette[]/**<The palette that will be displayed multiple times.*/,
	 			 int max/**<The max index of the image array.*/,
				 int height/**<The height of the screen.*/,
				 int width/**<The width of the screen.*/);

///Plasma effect loaded into image1.
void drawPlasma(char *image1/**<The temp image.*/,
	 			char *image2/**<The displayed image.*/,
	 			int palette[]/**<The palette for coloration.*/,
	 			int max/**<The max index of the image array.*/,
	 			int height/**<The height of the screen.*/,
	 			int width/**<The width of the screen.*/,
	 			int timer/**<The duration of the effect.*/);

#endif
