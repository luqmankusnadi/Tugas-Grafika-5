#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "framebuffer.h"
#include "image.h"
#include "bitmap.h"
#include "input.h"
#include "point.h"


//screen size
long int width, height;

int ClampInt(int x, int min, int max){
	return x > max ? max : (x < min ? min : x);
}

int main(){	
	Image windowImage = LoadBitmapAsImage("images/window.bmp");
	Image mapImage = LoadBitmapAsImage("images/map.bmp");

	
	InitFramebuffer(&width, &height);
	set_conio_terminal_mode();
	
	float scrollRate = 6;
	float minScale = 1;
	float maxScale = 2;
	float scale = minScale;
	int winW = 800/2;
	int winH = 600/2;
	
	while(1){
		ClearScreen();
		DrawImage(width/2, height/2, &mapImage, scale, 0);
		DrawImage(width/2, height/2, &windowImage, 1, 0);
		SwapBuffers();
		char c = getch();
		if(c == 'w'){ //scroll up
			mapImage.pivot.y -= (int)(scrollRate/scale); 
		} 
		else if(c == 's'){ //scroll down
			mapImage.pivot.y += (int)(scrollRate/scale); 
		}
		else if(c == 'a'){ //scroll left
			mapImage.pivot.x -= (int)(scrollRate/scale);
		}
		else if(c == 'd'){ //scroll right
			mapImage.pivot.x += (int)(scrollRate/scale);
		}
		else if(c == 'g'){ //zoom in
			scale += 0.1;
		}
		else if(c == 'h'){ //zoom out
			scale -= 0.1;
		}
		else if(c == 'x'){
			break;
		}
		scale = scale > maxScale ? maxScale : (scale < minScale ? minScale : scale);
		
		int scaledWinW = (int)((float)winW/scale);
		int scaledWinH = (int)((float)winH/scale);
		mapImage.pivot.x = ClampInt(mapImage.pivot.x, scaledWinW, mapImage.w - scaledWinW);
		mapImage.pivot.y = ClampInt(mapImage.pivot.y, scaledWinH, mapImage.h - scaledWinH);

	}
	FreeImage(&mapImage);
	FreeImage(&windowImage);
	return 0;
}
