#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL;
SDL_Surface *gImage = NULL;

bool init();
bool loadMedia();
SDL_Surface* loadSurface(string path);
void close();

int main(int argc, char *argv[])
{
	bool quit = false;
	SDL_Event e;

	if(!init())
	{
		printf("init failed.\n");
		close();
		return 0;
	}

	if(!loadMedia())
	{
		printf("loadMedia failed.\n");
		close();
		return 0;
	}

	while(!quit)
	{
		while(SDL_PollEvent(&e) == 1)
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}

			SDL_BlitScaled(gImage, NULL, gSurface, NULL);
			SDL_UpdateWindowSurface(gWindow);
		}
	}

	close();
	return 0;
}

bool init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL Init failed %s\n", SDL_GetError());
		return false;
	}

	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		printf("Img init failed %s\n", IMG_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("sexiest sdl window ever", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		printf("failed to create window %s\n", SDL_GetError());
		return false;
	}

	gSurface = SDL_GetWindowSurface(gWindow);
	if(gSurface == NULL)
	{
		printf("failed to get window surface %s\n");
		return false;
	}

	return true;
}

bool loadMedia()
{
	gImage = loadSurface("../media/colors.png");
	if(gImage == NULL)
	{
		printf("loadMedia failed for gImage\n");
		return false;
	}
	return true;
}

SDL_Surface* loadSurface(string path)
{
	SDL_Surface *loadedSurface = NULL;
	SDL_Surface *optimizedSurface = NULL;

	loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL)
	{
		printf("IMG load failed %s %s\n", path.c_str(), IMG_GetError());
		return NULL;
	}

	optimizedSurface = SDL_ConvertSurface(loadedSurface, gSurface->format, NULL);
	if(optimizedSurface == NULL)
	{
		printf("failed to optimize surface %s %s\n", path.c_str(), SDL_GetError());
		SDL_FreeSurface(loadedSurface);
		return NULL;
	}

	SDL_FreeSurface(loadedSurface);
	return optimizedSurface;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	SDL_FreeSurface(gSurface);
	SDL_FreeSurface(gImage);
	gWindow = NULL;
	gSurface = NULL;
	gImage = NULL;

	IMG_Quit();
	SDL_Quit();
}
