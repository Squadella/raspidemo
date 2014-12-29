//Our libraries
#include "libgmini.h"
#include "processing.h"
#include "alphabet.h"

//Other libraries
#include <stdio.h>
#include <stdlib.h>

void drawAlphabet(char letter, int resize, int *image, Pixel center, int width, int height, int thick)
{
	//Initialisations
	Pixel start, end;
	start.color=center.color;
	end.color=center.color;
	int max=width*height, index, i;

	switch (letter)
	{
		case 'A':
			for (i=0; i<thick; i++)
			{
				//Drawing the left part of A
				start.y=center.y+(5*resize);
				end.y=center.y-(6*resize);
				start.x=center.x-(4*resize)+i;
				end.x=center.x+i;
				if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
					if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
						drawLine(start, end, image, width, max);

				//Drawing the right part of A
				start.x=center.x+(4*resize)+i;
				if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
					if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
						drawLine(start, end, image, width, max);

				//Drawing the middle bar of A
				start.x=center.x-(2*resize);
				start.y=center.y+(1*resize)+i;
				index=(width*start.y)+start.x;
				//Place the point at the right place (cause by resizing)
				while(image[index]!=center.color && start.x>=0)
				{
					start.x--;
					index--;
				}
				end.x=center.x+(2*resize);
				end.y=center.y+(1*resize)+i;
				index=(width*end.y)+end.x;
				while(image[index]!=center.color && end.x>0)
				{
					end.x++;
					index++;
				}
				if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
					if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
						drawLine(start, end, image, width, max);
			}
			break;

		case 'D':
			//Drawing the vertical bar of D
			start.x=center.x-(4*resize);
			start.y=center.y+(6*resize);
			end.x=center.x-(4*resize);
			end.y=center.y-(5*resize);
			if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
				if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
					drawLine(start, end, image, width, max);

			//Drawing the circular part inferior of D
			drawQuarterCircle(center, 5*resize, image, height, width, 4);
			for(i=0; i<resize; i++)
			{
				center.y++;
			}
			drawQuarterCircle(center, 5*resize, image, height, width, 1);

			//Drawing line between circle and the D line
			for(i=0; i<resize; i++)
			{
				center.y--;
			}
			start.x=center.x-(4*resize);
			start.y=center.y+(6*resize);
			end.x=(center.x-(4*resize))+1;
			end.y=center.y+(6*resize);
			index=(width*end.y)+end.x;
			while(image[index]!=center.color && end.x<width)
			{
				end.x++;
				index++;
			}
			if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
				if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
					drawLine(start, end, image, width, max);
			start.x=center.x-(4*resize);
			start.y=center.y-(5*resize);
			end.x=(center.x-(4*resize))+1;
			end.y=center.y-(5*resize);
			index=(width*end.y)+end.x;
			while(image[index]!=center.color && end.x<width)
			{
				end.x++;
				index++;
			}
			if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
				if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
					drawLine(start, end, image, width, max);

			//Drawing line between the two quarters
			start.x=center.x+(5*resize);
			start.y=center.y;
			end.x=center.x+(5*resize);
			end.y=center.y+resize;
			if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
				if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
					drawLine(start, end, image, width, max);
			break;

		case 'E':
			//Drawing the vertical line of E
			start.x=center.x-(4*resize);
			start.y=center.y-(5*resize);
			end.x=center.x-(4*resize);
			end.y=center.y+(6*resize);
			if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
				if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
					drawLine(start, end, image, width, max);

			//Drawing the superior vertical line
			end.x=center.x+(3*resize);
			end.y=center.y-(5*resize);
			if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
				if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
					drawLine(start, end, image, width, max);

			//Drawing the middle vertical line
			start.y=start.y+(5*resize);
			end.y=end.y+(5*resize);
			if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
				if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
					drawLine(start, end, image, width, max);

			//Drawing the bottom line
			start.y=start.y+(6*resize);
			end.y=end.y+(6*resize);
			if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
				if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
					drawLine(start, end, image, width, max);
			break;

		case 'M':
			//Drawing the left vertial line
			start.x=center.x-(5*resize);
			start.y=center.y-(5*resize);
			end.x=center.x-(5*resize);
			end.y=center.y+(6*resize);
			if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
				if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
					drawLine(start, end, image, width, max);

			//Drawing the right vertical line
			start.x+=10*resize;
			end.x+=10*resize;
			if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
				if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
					drawLine(start, end, image, width, max);

			//Drawing the right center of M
			end.x=center.x;
			end.y=center.y+(4*resize);
			if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
				if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
					drawLine(start, end, image, width, max);

			//Drawing the left center of M
			start.x-=10*resize;
			if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
				if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
					drawLine(start, end, image, width, max);
			break;

		case 'O':
			//Drawing the top half circle
			drawQuarterCircle(center, 5*resize, image, height, width, 3);
			drawQuarterCircle(center, 5*resize, image, height, width, 4);

			//Drawing the bottom half circle
			start.y=center.y+resize;
			start.x=center.x;
			drawQuarterCircle(start, 5*resize, image, height, width, 1);
			drawQuarterCircle(start, 5*resize, image, height, width, 2);

			//Drawing a line between the two half circles in the right
			start.x=center.x+(5*resize);
			start.y=center.y;
			end.x=center.x+(5*resize);
			end.y=center.y+resize;
			if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
				if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
					drawLine(start, end, image, width, max);

			//Drawing a line between the two half circles in the left
			start.x-=10*resize;
			end.x-=10*resize;
			if (end.x>=0 && end.y<=height && end.x<=width && end.y>=0)
				if (start.x>=0 && start.y<=height && start.x<=width && start.y>=0)
					drawLine(start, end, image, width, max);
			break;

		default:
			return;
	}
}

void drawQuarterCircle(const Pixel center, int radius, int *image, int height, int width, int quarter)
{
	Pixel pixel, temp;
	int max=height*width;
	int err = 2-2*radius;
	pixel.x = -radius;
	pixel.y = 0;
	switch (quarter)
	{
		case 1: //The inferior right quarter
		do
		{
			temp.x = center.x-pixel.x;
			temp.y = center.y+pixel.y;
			temp.color=center.color;
			if (temp.x>=0 && temp.y<=height && temp.x<=width && temp.y>=0)
			{
				drawPixel(temp, image, width, max);
			}
			radius = err;
			if (radius <= pixel.y) err += ++(pixel.y)*2+1;           //e_xy+e_y < 0
			if (radius > pixel.x || err > pixel.y) err += ++(pixel.x)*2+1; //e_xy+e_x > 0 or no 2nd y-step
		} while (pixel.x < 0);
		break;

		case 2: //The inferior left quarter
		do
		{
			temp.x = center.x-pixel.y;
			temp.y = center.y-pixel.x;
			temp.color=center.color;
			if (temp.x>=0 && temp.y<=height && temp.x<=width && temp.y>=0)
			{
				drawPixel(temp, image, width, max);
			}
			radius = err;
			if (radius <= pixel.y) err += ++(pixel.y)*2+1;           //e_xy+e_y < 0
			if (radius > pixel.x || err > pixel.y) err += ++(pixel.x)*2+1; //e_xy+e_x > 0 or no 2nd y-step
		} while (pixel.x < 0);
		break;

		case 3: //The superior right quarter
		do
		{
			temp.x = center.x+pixel.x;
			temp.y = center.y-pixel.y;
			temp.color=center.color;
			if (temp.x>=0 && temp.y<=height && temp.x<=width && temp.y>=0)
			{
				drawPixel(temp, image, width, max);
			}
			radius = err;
			if (radius <= pixel.y) err += ++(pixel.y)*2+1;           //e_xy+e_y < 0
			if (radius > pixel.x || err > pixel.y) err += ++(pixel.x)*2+1; //e_xy+e_x > 0 or no 2nd y-step
		} while (pixel.x < 0);
		break;

		case 4: //The superior left quarter
		do
		{
			temp.x = center.x+pixel.y;
			temp.y = center.y+pixel.x;
			temp.color=center.color;
			if (temp.x>=0 && temp.y<=height && temp.x<=width && temp.y>=0)
			{
				drawPixel(temp, image, width, max);
			}
			radius = err;
			if (radius <= pixel.y) err += ++(pixel.y)*2+1;           //e_xy+e_y < 0
			if (radius > pixel.x || err > pixel.y) err += ++(pixel.x)*2+1; //e_xy+e_x > 0 or no 2nd y-step
		} while (pixel.x < 0);
		break;

		default:
			return;
	}
}