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

LTexture gBackground;
LTexture gColors;
LTexture gColors2;
LTexture gColors3;

bool init();
bool loadMedia();
void close();

int main(int argc, char *argv[])
{
	bool quit = false;
	SDL_Event e;

	Uint8 alphaMod = 255;

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
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(gRenderer);

		gBackground.render(0, 0, NULL);
		gColors.setAlphaMod(alphaMod);
		gColors.render(0, SCREEN_HEIGHT / 2, NULL);
		gColors2.setAlphaMod(alphaMod);
		gColors2.render(gColors2.getWidth(), SCREEN_HEIGHT / 2, NULL);
		gColors3.setAlphaMod(alphaMod);
		gColors3.render(SCREEN_WIDTH - gColors.getWidth(), SCREEN_HEIGHT / 2, NULL);

		SDL_RenderPresent(gRenderer);

		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT)
		{
			quit = true;
		}
		else if(e.type == SDL_KEYDOWN)
		{
			switch(e.key.keysym.sym)
			{
				case SDLK_UP:
					alphaMod += 5;
					break;
				case SDLK_DOWN:
					alphaMod -= 5;
					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
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
		printf("SDL init failed %s\n", SDL_GetError());
		return false;
	}
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("warning linear texture filtering not enabled\n");
	}

	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		printf("IMG init failed %s\n", IMG_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("sdl tutorial 13", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
	if(gWindow == NULL)
	{
		printf("createWindow failed %s\n", SDL_GetError());
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(gRenderer == NULL)
	{
		printf("failed to create renderer %s\n", SDL_GetError());
		return false;
	}

	return true;
}

bool loadMedia()
{
	if(!gBackground.loadFromFile("../media/background.png"))
	{
		printf("failed to load background\n");
		return false;
	}
	if(!gColors.loadFromFile("../media/dots.png"))
	{
		printf("failed to load colors\n");
		return false;
	}
	gColors.setBlendMode(SDL_BLENDMODE_ADD);

	if(!gColors2.loadFromFile("../media/dots.png"))
	{
		printf("failed to load colors2\n");
		return false;
	}
	gColors2.setBlendMode(SDL_BLENDMODE_BLEND);

	if(!gColors3.loadFromFile("../media/dots.png"))
	{
		printf("failed to load colors3\n");
		return false;
	}
	gColors3.setBlendMode(SDL_BLENDMODE_MOD);

	return true;
}

void close()
{
	gBackground.free();
	gColors.free();
	gColors2.free();
	gColors3.free();
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);

	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}
