/* compile with -lXext gcc option */

#include "libgmini.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XShm.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define FAILURE 0
#define SUCCESS 1
#define __FUNCTION_KEY__ 0xFF
#define __ESCAPE_KEY__ 0x1B

typedef unsigned int int32;
typedef unsigned short int16;
typedef unsigned short short16;
typedef unsigned char char8;
typedef void (*CONVERTER) (void *src, void *dst, int pixels);
static int process_events (void);
static Display *display;
static int screen;
static int screen_width;
static int screen_height;
static int viewport_width;
static int viewport_height;
static int depth;
static Window root_window;
static Visual *visual;
static char *buffer;
static int pixmap_format_count;
static int pixmap_counter;
static int converter_depth;
static XPixmapFormatValues *pixmap_formats;
static Window window;
static int x_position;
static int y_position;
static XSetWindowAttributes window_attributes;
static XSizeHints window_sizehints;
static GC window_gc;
static XImage *ximage;
static XShmSegmentInfo shm_segment;
static CONVERTER convert;
static int output_pitch;
static int blitcounter;
static int source_index;
static int destination_index;

int colorRGB(int r, int g, int b) {
	return( r<<16 | g<<8 | b );
}

void invertRGB(int color, int *red, int *green, int *blue)
{
	*red=color/65536;
	*green=(color%65536)/256;
	*blue=color % 256;
}

void convert_32_to_32_rgb888(void *src, void *dst, int pixels) {
	int32 *p = (int32 *) src;
	int32 *q = (int32 *) dst;
	while(pixels--)
		*(q++) = *(p++);
}

void convert_32_to_32_bgr888(void *src, void *dst, int pixels) {
	int32 *p = (int32 *) src;
	int32 *q = (int32 *) dst;
	while(pixels--) {
		int32 r = (int32) ((*p & 0x00FF0000) >> 16);
		int32 g = (int32) ((*p & 0x0000FF00));
		int32 b = (int32) ((*p & 0x000000FF) << 16);
		*(q++) = r | g | b;
		p++;
	}
}

void convert_32_to_24_rgb888(void *src, void *dst, int pixels) {
	char8 *p = (char8 *) src;
	char8 *q = (char8 *) dst;
	while(pixels--) {
		*(q + 2) = *p;
		*(q + 1) = *(p + 1);
		*q = *(p + 2);
		p += 4;
		q += 3;
	}
}

void convert_32_to_24_bgr888(void *src, void *dst, int pixels) {
	char8 *p = (char8 *) src;
	char8 *q = (char8 *) dst;
	while(pixels--) {
		*q = *p;
		*(q + 1) = *(p + 1);
		*(q + 2) = *(p + 2);
		p += 4;
		q += 3;
	}
}

void convert_32_to_16_rgb565(void *src, void *dst, int pixels) {
	int32 *p = (int32 *) src;
	short16 *q = (short16 *) dst;
	while(pixels--) {
		short16 r = (short16) ((*p & 0x00F80000) >> 8);
		short16 g = (short16) ((*p & 0x0000FC00) >> 5);
		short16 b = (short16) ((*p & 0x000000F8) >> 3);
		*q = r | g | b;
		p++;
		q++;
	}
}

void convert_32_to_16_bgr565(void *src, void *dst, int pixels) {
	int32 *p = (int32 *) src;
	short16 *q = (short16 *) dst;
	while(pixels--) {
		short16 r = (short16) ((*p & 0x00F80000) >> 19);
		short16 g = (short16) ((*p & 0x0000FC00) >> 5);
		short16 b = (short16) ((*p & 0x000000F8) << 8);
		*q = r | g | b;
		p++;
		q++;
	}
}

void convert_32_to_16_rgb555(void *src, void *dst, int pixels) {
	int32 *p = (int32 *) src;
	short16 *q = (short16 *) dst;
	while(pixels--) {
		short16 r = (short16) ((*p & 0x00F80000) >> 9);
		short16 g = (short16) ((*p & 0x0000F800) >> 6);
		short16 b = (short16) ((*p & 0x000000F8) >> 3);
		*q = r | g | b;
		p++;
		q++;
	}
}

void convert_32_to_16_bgr555(void *src, void *dst, int pixels) {
	int32 *p = (int32 *) src;
	short16 *q = (short16 *) dst;
	while(pixels--) {
		short16 r = (short16) ((*p & 0x00F80000) >> 20);
		short16 g = (short16) ((*p & 0x0000F800) >> 6);
		short16 b = (short16) ((*p & 0x000000F8) << 8);
		*q = r | g | b;
		p++;
		q++;
	}
}

CONVERTER request_converter(int bits, int32 r, int32 g, int32 b) {
	if(bits == 32 && r == 0x00FF0000 && g == 0x0000FF00 && b == 0x000000FF)
		return &convert_32_to_32_rgb888;
	if(bits == 32 && r == 0x000000FF && g == 0x0000FF00 && b == 0x00FF0000)
		return &convert_32_to_32_bgr888;
	if(bits == 24 && r == 0x00FF0000 && g == 0x0000FF00 && b == 0x000000FF)
		return &convert_32_to_24_rgb888;
	if(bits == 24 && r == 0x000000FF && g == 0x0000FF00 && b == 0x00FF0000)
		return &convert_32_to_24_bgr888;
	if(bits == 16 && r == 0xF800 && g == 0x07E0 && b == 0x001F)
		return &convert_32_to_16_rgb565;
	if(bits == 16 && r == 0x001F && g == 0x07E0 && b == 0xF800)
		return &convert_32_to_16_bgr565;
	if(bits == 16 && r == 0x7C00 && g == 0x03E0 && b == 0x001F)
		return &convert_32_to_16_rgb555;
	if(bits == 16 && r == 0x001F && g == 0x03E0 && b == 0x7C00)
		return &convert_32_to_16_bgr555;
	return 0;
}

int mini_open(char *title, int width, int height) {
	display = XOpenDisplay(NULL);
	if(display == NULL)
		return FAILURE;
	screen = DefaultScreen(display);
	visual = DefaultVisual(display, screen);
	depth = DefaultDepth(display, screen);
	pixmap_formats = XListPixmapFormats(display, &pixmap_format_count);
	for(pixmap_counter = 0; pixmap_counter < pixmap_format_count; pixmap_counter++)
		if(depth == pixmap_formats[pixmap_counter].depth)
			converter_depth = pixmap_formats[pixmap_counter].bits_per_pixel;
	XFree(pixmap_formats);
	convert = request_converter(converter_depth, visual->red_mask, visual->green_mask, visual->blue_mask);
	if(!convert) {
		XCloseDisplay(display);
		return 0;
	}
	switch(converter_depth) {
		case 8: output_pitch = 1; break;
		case 15: output_pitch = 2; break;
		case 16: output_pitch = 2; break;
		case 24: output_pitch = 3; break;
		case 32: output_pitch = 4; break;
	}
	buffer = (char *) malloc(width * height * output_pitch);
	if(buffer == NULL) {
		XCloseDisplay(display);
		return FAILURE;
	}
	if(!XShmQueryExtension(display)) {
		XCloseDisplay(display);
		return FAILURE;
	}
	screen_width = DisplayWidth(display, screen);
	screen_height = DisplayHeight(display, screen);
	root_window = DefaultRootWindow(display);
	window_attributes.border_pixel = BlackPixel (display, screen);
	window_attributes.background_pixel = BlackPixel (display, screen);
	window_attributes.backing_store = NotUseful;
	x_position = 0;
	y_position = 0;
	/*
	   x_position = (screen_width - width) / 2;
	   y_position = (screen_height - height) / 2;
	 */
	window = XCreateWindow(display, root_window, x_position, y_position, width, height, 0, depth, InputOutput, visual, CWBackPixel | CWBorderPixel | CWBackingStore, &window_attributes);
	XStoreName(display, window, title);
	XSelectInput(display, window, KeyPressMask | KeyReleaseMask);
	window_sizehints.flags = PPosition | PMinSize | PMaxSize;
	window_sizehints.x = 0;
	window_sizehints.y = 0;
	window_sizehints.min_width = width;
	window_sizehints.max_width = width;
	window_sizehints.min_height = height;
	window_sizehints.max_height = height;
	XSetWMNormalHints(display, window, &window_sizehints);
	XClearWindow(display, window);
	XMapRaised(display, window);
	XFlush(display);
	window_gc = DefaultGC(display, screen);
	ximage = XShmCreateImage(display, visual, depth, ZPixmap, 0, &shm_segment, width, height);
	shm_segment.shmid = shmget(IPC_PRIVATE, ximage->bytes_per_line * ximage->height, IPC_CREAT | 0777);
	ximage->data = (char *)shmat(shm_segment.shmid, 0, 0);
	shm_segment.shmaddr = ximage->data;
	shm_segment.readOnly = False;
	if(!XShmAttach(display, &shm_segment)) {
		XDestroyImage(ximage);
		shmdt(shm_segment.shmaddr);
		shmctl(shm_segment.shmid, IPC_RMID, 0);
		XDestroyWindow(display, window);
		XCloseDisplay(display);
		return FAILURE;
	}
	viewport_width = width;
	viewport_height = height;
	return SUCCESS;
}

void mini_close(void) {
	XShmDetach(display, &shm_segment);
	XDestroyImage(ximage);
	shmdt(shm_segment.shmaddr);
	shmctl(shm_segment.shmid, IPC_RMID, 0);
	XDestroyWindow(display, window);
	XCloseDisplay(display);
	if(buffer)
		free(buffer);
}

int mini_update(void *buffer) { 
	char *buffer_tmp;
	buffer_tmp=(char *)buffer;
	source_index = 0;
	destination_index = 0;
	for(blitcounter = 0; blitcounter < viewport_height; blitcounter++) {
		convert(buffer_tmp + source_index, (ximage->data) + destination_index, viewport_width);
		source_index += viewport_width * sizeof (int);
		destination_index += viewport_width * output_pitch;
	}
	XSync(display, 0);
	XShmPutImage(display, window, window_gc, ximage, 0, 0, 0, 0, viewport_width, viewport_height, False);
	if(process_events ()) {
		mini_close();
		exit(0);
	}
	return SUCCESS;
}

int process_events(void) {
	XEvent xevent;
	KeySym keysym;
	if(XPending(display)) {
		XNextEvent(display, &xevent);
		if(xevent.type == KeyPress) {
			keysym = XLookupKeysym(&xevent.xkey, 0);
			if((keysym >> 8) == __FUNCTION_KEY__)
				if((keysym & 0xFF) == __ESCAPE_KEY__)
					return SUCCESS;
		}
	}
	return FAILURE;
}
