#include <stdio.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL;
SDL_Surface *gBackground = NULL;

bool init();
bool loadMedia();
void close();

SDL_Surface* loadSurface(std::string path);

int main(int argc, char *argv[])
{
	bool toquit = false;
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

	while(!toquit)
	{
		SDL_BlitScaled(gBackground, NULL, gSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);

		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				toquit = true;
			}
			else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
			{
				toquit = true;
			}
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

	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		printf("img init failed %s\n", IMG_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("SDL tutorial 6", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	gBackground = loadSurface("../media/test.png");
	if(gBackground == NULL)
	{
		printf("loadSurface failed for background\n");
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
	gSurface = gBackground = NULL;

	IMG_Quit();
	SDL_Quit();
}

SDL_Surface* loadSurface(std::string path)
{
	SDL_Surface *loadedSurface = NULL, *optimizedSurface = NULL;

	loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL)
	{
		printf("img_load failed for %s error %s\n", path.c_str(), IMG_GetError());
		return NULL;
	}

	optimizedSurface = SDL_ConvertSurface(loadedSurface, gSurface->format, 0);
	if(optimizedSurface == NULL)
	{
		printf("failed to optimize surface %s\n", SDL_GetError());
		SDL_FreeSurface(loadedSurface);
		return NULL;
	}
	SDL_FreeSurface(loadedSurface);
	return optimizedSurface;
}
