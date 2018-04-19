#include "LTexture.h"
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;

LTexture gTexture;

bool init();
bool loadMedia();
void close();

int main(int argc, char *argv[])
{
	bool quit = false;
	SDL_Event e;

	if(!init())
	{
		printf("init failed\n");
		return 0;
	}
	if(!loadMedia())
	{
		printf("load media failed\n");
		return 0;
	}

	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderClear(gRenderer);

	while(!quit)
	{
		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT)
		{
			quit = true;
		}

		gTexture.render((SCREEN_WIDTH - gTexture.getWidth()) / 2, (SCREEN_HEIGHT - gTexture.getHeight()) / 2, NULL, 30, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(gRenderer);

	}

	close();
	printf("thanks for playing\n");
	return 0;
}


bool init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("sdl init failed error %s\n", SDL_GetError());
		return false;
	}
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"))
	{
		printf("warning linear filtering not enabled\n");
	}

	if(TTF_Init() == -1)
	{
		printf("ttf init failed %s\n", TTF_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("sdl tutorial 16", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		printf("createwindow failed %s\n", SDL_GetError());
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
	SDL_Color red{255, 0, 0, 255};


	gFont = TTF_OpenFont("../media/xiro.ttf", 28);
	if(gFont == NULL)
	{
		printf("openfont failed %s\n", TTF_GetError());
		return false;
	}

	if(!gTexture.loadFromRenderedText("What am I doing\nhere?", &red))
	{
		printf("loadfromrenderedtext failed\n");
		return false;
	}
	return true;

}

void close()
{
	gTexture.free();
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	TTF_CloseFont(gFont);
	gFont = NULL;
	gWindow = NULL;
	gRenderer = NULL;

	TTF_Quit();
	SDL_Quit();
}
