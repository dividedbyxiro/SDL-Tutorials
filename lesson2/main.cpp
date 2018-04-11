#include <stdio.h>
#include <SDL.h>

bool init();
bool loadMedia();
void close();

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL;
SDL_Surface *gHello = NULL;

int main(int argc, char *argv[])
{
	if(!init())
	{
		printf("init failed\n");
		close();
		return 0;
	}

	if(!loadMedia())
	{
		printf("load media failed\n");
		close();
		return 0;
	}

	SDL_Rect dest;
	dest.h = 50;
	dest.w = 10;
	dest.x = 50;
	dest.y = 400;
	SDL_BlitScaled(gHello, NULL, gSurface, &dest);

	SDL_UpdateWindowSurface(gWindow);
	SDL_Delay(2000);

	close();
	return 0;

}


bool init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Init failed : %s\n", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("SDL Tutorial 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if(gWindow == NULL)
	{
		printf("failed to create window %s\n", SDL_GetError());
		return false;
	}

	gSurface = SDL_GetWindowSurface(gWindow);
	return true;
}

bool loadMedia()
{
	gHello = SDL_LoadBMP("../media/dot.bmp");

	if(gHello == NULL)
	{
		printf("failed to load image %s\n", SDL_GetError());
		return false;
	}
	return true;
}

void close()
{
	SDL_FreeSurface(gSurface);
	SDL_DestroyWindow(gWindow);
	gSurface = NULL;
	gWindow = NULL;
	SDL_Quit();
}
