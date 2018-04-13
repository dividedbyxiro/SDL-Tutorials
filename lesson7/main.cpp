#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gTexture = NULL;

bool init();
bool loadMedia();
void close();

SDL_Texture* loadTexture(string path);

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
		SDL_RenderClear(gRenderer);
		SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
		SDL_RenderPresent(gRenderer);

		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
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

	gWindow = SDL_CreateWindow("sdl tutorial 7", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		printf("failed to create window %s\n", SDL_GetError());
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(gRenderer == NULL)
	{
		printf("renderer couldn't be created %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	return true;
}

bool loadMedia()
{
	gTexture = loadTexture("../media/test.png");
	if(gTexture == NULL)
	{
		printf("loadTexture failed\n");
		return false;
	}
	return true;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyTexture(gTexture);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gTexture = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(string path)
{
	SDL_Surface *loadedSurface = NULL;
	SDL_Texture *newTexture = NULL;

	SDL_Surface *gTurret = NULL;

	loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL)
	{
		printf("img_load failed for %s error %s\n", path.c_str(), IMG_GetError());
		return NULL;
	}
	gTurret = IMG_Load("../media/piskel turret.png");
	SDL_Rect dest;
	dest.h = 100;
	dest.w = 50;
	dest.x = 200;
	dest.y = 20;
	SDL_BlitScaled(gTurret, NULL, loadedSurface, &dest);

	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if(newTexture == NULL)
	{
		printf("failed to create texture from surface %s error %s\n", path.c_str(), SDL_GetError());
		SDL_FreeSurface(loadedSurface);
		return NULL;
	}

	SDL_FreeSurface(gTurret);
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}
