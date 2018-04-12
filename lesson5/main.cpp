#include <stdio.h>
#include <SDL.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();
SDL_Surface* loadSurface(std::string filePath);

SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL;
SDL_Surface *gBackground = NULL;

int main(int argc, char *argv[])
{
	bool quit = false;
	SDL_Event e;

	if(!init())
	{
		printf("init failed\n");
		close();
		return 0;
	}

	if(!loadMedia())
	{
		printf("loadMedia failed\n");
		close();
		return 0;
	}

	while(!quit)
	{
		SDL_BlitScaled(gBackground, NULL, gSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);

		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT)
		{
			quit = true;
		}
	}

	close();
	printf("thanks for playing\n");
	return 0;
}

bool init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("sdl init failed %s\n", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("SDL tutorial 5", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	gBackground = loadSurface("../media/background.bmp");

	if(gBackground == NULL)
	{
		printf("loadSurface failed\n");
		return false;
	}

	return true;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	SDL_FreeSurface(gSurface);
	SDL_FreeSurface(gBackground);
	gWindow = NULL;
	gSurface = NULL;
	gBackground = NULL;

	SDL_Quit();
}

SDL_Surface* loadSurface(std::string filePath)
{
	SDL_Surface *loadedSurface;
	SDL_Surface *optimizedSurface;

	loadedSurface = SDL_LoadBMP(filePath.c_str());
	if(loadedSurface == NULL)
	{
		printf("loadbmp failed %s\n", SDL_GetError());
		return NULL;
	}

	optimizedSurface = SDL_ConvertSurface(loadedSurface, gSurface->format, NULL);
	if(optimizedSurface == NULL)
	{
		printf("failed to optimize surface %s\n", SDL_GetError());
		SDL_FreeSurface(loadedSurface);
		return NULL;
	}
	SDL_FreeSurface(loadedSurface);
	return optimizedSurface;
}
