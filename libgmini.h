#ifndef LIBG
#define LIBG

//Transform three integer into one readable by the graphics
unsigned int colorRGB(unsigned int r, unsigned int g, unsigned int b);
//Transform an int of color into red, green et blue
void invertRGB(unsigned int color, unsigned int *red, unsigned int *green, unsigned int *blue);
//Open a window
int mini_open (char*, int, int);
//Refresh the window
int mini_update (void*);
//Close the window
void mini_close ();

#endif