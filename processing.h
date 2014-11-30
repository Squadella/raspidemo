#ifndef LIBPRO
#define LIBPRO

void open_ppm(int image[]);
void drawPixel(int x, int y, int color, int image[], int width, int max);
void drawLine(int x0, int y0, int x1, int y1, int color, int image[], int width, int max);


#endif