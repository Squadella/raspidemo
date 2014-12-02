#ifndef LIBPRO
#define LIBPRO

typedef struct Pixel{
	int x;
	int y;
	int color;
}Pixel;

void open_ppm(int image[]);
void drawPixel(Pixel pixel, int image[], int width, int max);
void drawLine(Pixel start, Pixel end, int image[], int width, int max);
void starField(int image[], int max, int color);

#endif