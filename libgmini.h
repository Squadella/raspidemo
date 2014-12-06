#ifndef LIBG
#define LIBG

//Transform three integer in one readable by the graphics
int colorRGB(int r, int g, int b);
//Open a window
int mini_open (char*, int, int);
//Refresh the window
int mini_update (void*);
//Close the window
void mini_close ();

#endif