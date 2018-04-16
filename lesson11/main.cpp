#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "LTexture.h"

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

enum COLOR
{
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAX_COLORS
};

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

LTexture gDots;

SDL_Rect gRects[MAX_COLORS];

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
		close();
		return 0;
	}

	if(!loadMedia())
	{
		printf("init failed\n");
		close();
		return 0;
	}

	while(!quit)
	{
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(gRenderer);

		gDots.render(0, 0, &gRects[RED]);
		gDots.render(SCREEN_WIDTH - gRects[GREEN].w, 0, &gRects[GREEN]);
		gDots.render(0, SCREEN_HEIGHT - gRects[YELLOW].h, &gRects[YELLOW]);
		gDots.render(SCREEN_WIDTH - gRects[BLUE].w, SCREEN_HEIGHT - gRects[BLUE].h, &gRects[BLUE]);

		SDL_RenderPresent(gRenderer);

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
	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		printf("img init failed %s\n", IMG_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("sdl tutorial 11", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		printf("createwindow failed %s\n", SDL_GetError());
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(gRenderer == NULL)
	{
		printf("createrenderer failed %s\n", SDL_GetError());
		return false;
	}
	return true;
}

bool loadMedia()
{
	if(!gDots.loadFromFile("../media/dots.png"))
	{
		printf("failed to load dots\n");
		return false;
	}

	gRects[RED].x = 0;
	gRects[RED].y = 0;

	gRects[GREEN].x = 100;
	gRects[GREEN].y = 0;

	gRects[YELLOW].x = 0;
	gRects[YELLOW].y = 100;

	gRects[BLUE].x = 100;
	gRects[BLUE].y = 100;

//	for(SDL_Rect rect : gRects)
//	{
//		printf("setting dimensions for rect\n");
//		rect.h = 100;
//		rect.w = 100;
//	}

//	gRects[RED].h = gRects[RED].w = 100;

	for(int i = 0; i < MAX_COLORS; i++)
	{
		gRects[i].h = gRects[i].w = 100;
	}

	return true;
}

void close()
{
	gDots.free();
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}
