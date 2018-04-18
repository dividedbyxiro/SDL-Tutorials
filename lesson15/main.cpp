#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "LTexture.h"

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

LTexture gTurret;

bool init();
bool loadMedia();
void close();

int main(int argc, char *argv[])
{
	bool quit = false;
	SDL_Event e;
	int angle = 0;

	int direction = 1;
	bool stopped = false;

	if(!init())
	{
		printf("init failed\n");
		return 0;
	}

	if(!loadMedia())
	{
		printf("loadMedia failed\n");
		return 0;
	}

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);

	while(!quit)
	{
		SDL_RenderClear(gRenderer);
		gTurret.render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, NULL, angle, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(gRenderer);

		if(!stopped)
		{
			angle += direction;
			angle %= 360;
		}

		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
			{
				stopped = true;
			}
			else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE)
			{
				stopped = false;
				direction *= -1;
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

	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("warning, linear filtering not set\n");
	}

	gWindow = SDL_CreateWindow("sdl tutorial 15", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		printf("createWindow failed %s\n", SDL_GetError());
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(gRenderer == NULL)
	{
		printf("createRenderer failed %s\n", SDL_GetError());
		return false;
	}

	return true;
}

bool loadMedia()
{
	if(!gTurret.loadFromFile("../media/piskel turret.png"))
	{
		printf("failed to load turret\n");
		return false;
	}

	return true;
}

void close()
{
	gTurret.free();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gRenderer = NULL;
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}
