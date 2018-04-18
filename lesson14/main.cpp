#include "LTexture.h"
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

LTexture gFoo;
LTexture gBackground;

SDL_Rect frames[4];

bool init();
bool loadMedia();
void close();

int main(int argc, char *argv[])
{
	bool quit = false;
	SDL_Event e;
	int frameLength = 0;
	int currentFrame = 0;

	int lastTime = 0;

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

	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

	while(!quit)
	{
		SDL_RenderClear(gRenderer);
		gBackground.render(0, 0, NULL);
		gFoo.render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, &frames[currentFrame]);
		frameLength++;
		if(frameLength > 4)
		{
			frameLength = 0;
			currentFrame = (currentFrame + 1) % 4;
		}
		SDL_RenderPresent(gRenderer);

		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		printf("time between renders = %d ms\n", SDL_GetTicks() - lastTime);
		lastTime = SDL_GetTicks();

//		SDL_Delay(1000 / 60);
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
		printf("warning, linear filtering not enabled");
	}

	gWindow = SDL_CreateWindow("sdl tutorial 14", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		printf("create window failed %s\n", SDL_GetError());
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if(gRenderer == NULL)
	{
		printf("createRenderer failed %s\n", SDL_GetError());
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

	if(!gFoo.loadFromFile("../media/animatedfoo.png"))
	{
		printf("failed to load animated foo\n");
		return false;
	}

	for(int i = 0; i < 4; i++)
	{
		frames[i].x = i * 64;
		frames[i].y = 0;
		frames[i].h = gFoo.getHeight();
		frames[i].w = 64;
	}
	return true;
}

void close()
{
	gBackground.free();
	gFoo.free();
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;
	IMG_Quit();
	SDL_Quit();
}
