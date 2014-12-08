#ifndef LIBG
#define LIBG

//Transform three integer into one readable by the graphics
int colorRGB(int r, int g, int b);
//Transform an int of color into red, green et blue
void invertRGB(int color, int *red, int *green, int *blue);
//Open a window
int mini_open (char*, int, int);
//Refresh the window
int mini_update (void*);
//Close the window
void mini_close ();

#endif