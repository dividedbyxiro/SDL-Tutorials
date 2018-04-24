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

LTexture gButtonTexture;

enum MOUSE_STATE
{
	MOUSE_OUT,
	MOUSE_OVER,
	MOUSE_BUTTON_PRESSED,
	MOUSE_BUTTON_RELEASED,
	MOUSE_STATE_TOTAL
};

SDL_Rect gFrames[MOUSE_STATE_TOTAL];
MOUSE_STATE currentStates[4];
SDL_Rect gButtons[4];

bool init();
bool loadMedia();
void close();

void handleInput(SDL_Event *e);

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

		for(int i = 0; i < 4; i++)
		{
			gButtonTexture.render(gButtons[i].x, gButtons[i].y, &gFrames[currentStates[i]], 0, NULL, SDL_FLIP_NONE);
		}
		SDL_RenderPresent(gRenderer);

		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
			handleInput(&e);
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
		printf("warning linear filtering not enabled\n");
	}

	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		printf("img init failed %s\n", IMG_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("sdl tutorial 17", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	if(!gButtonTexture.loadFromFile("../media/buttons.png"))
	{
		printf("failed to load buttons texture\n");
		return false;
	}

	gFrames[MOUSE_OUT].x = 0;
	gFrames[MOUSE_OUT].y = gButtonTexture.getHeight() / 4 * 0;
	gFrames[MOUSE_OUT].w = 300;
	gFrames[MOUSE_OUT].h = gButtonTexture.getHeight() / 4;

	gFrames[MOUSE_OVER].x = 0;
	gFrames[MOUSE_OVER].y = gButtonTexture.getHeight() / 4 * 1;
	gFrames[MOUSE_OVER].w = 300;
	gFrames[MOUSE_OVER].h = gButtonTexture.getHeight() / 4;

	gFrames[MOUSE_BUTTON_PRESSED].x = 0;
	gFrames[MOUSE_BUTTON_PRESSED].y = gButtonTexture.getHeight() / 4 * 2;
	gFrames[MOUSE_BUTTON_PRESSED].w = 300;
	gFrames[MOUSE_BUTTON_PRESSED].h = gButtonTexture.getHeight() / 4;

	gFrames[MOUSE_BUTTON_RELEASED].x = 0;
	gFrames[MOUSE_BUTTON_RELEASED].y = gButtonTexture.getHeight() / 4 * 3;
	gFrames[MOUSE_BUTTON_RELEASED].w = 300;
	gFrames[MOUSE_BUTTON_RELEASED].h = gButtonTexture.getHeight() / 4;

	gButtons[0].x = 0;
	gButtons[0].y = 0;
	gButtons[0].w = SCREEN_WIDTH / 2;
	gButtons[0].h = SCREEN_HEIGHT / 2;

	gButtons[1].x = SCREEN_WIDTH / 2;
	gButtons[1].y = 0;
	gButtons[1].w = SCREEN_WIDTH / 2;
	gButtons[1].h = SCREEN_HEIGHT / 2;

	gButtons[2].x = 0;
	gButtons[2].y = SCREEN_HEIGHT / 2;
	gButtons[2].w = SCREEN_WIDTH / 2;
	gButtons[2].h = SCREEN_HEIGHT / 2;

	gButtons[3].x = SCREEN_WIDTH / 2;
	gButtons[3].y = SCREEN_HEIGHT / 2;
	gButtons[3].w = SCREEN_WIDTH / 2;
	gButtons[3].h = SCREEN_HEIGHT / 2;

	return true;

}

void close()
{
	gButtonTexture.free();
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

void handleInput(SDL_Event *e)
{
	int x, y;
	for(int i = 0; i < 4; i++)
	{
		if(e->type == SDL_MOUSEBUTTONDOWN)
		{
			currentStates[i] = MOUSE_BUTTON_PRESSED;
			continue;
		}
		else if(e->type == SDL_MOUSEBUTTONUP)
		{
			currentStates[i] = MOUSE_BUTTON_RELEASED;
			continue;
		}
		else if(e->type == SDL_MOUSEMOTION)
		{
			SDL_GetMouseState(&x, &y);
			if(x > gButtons[i].x && x < gButtons[i].x + gButtons[i].w && y > gButtons[i].y && y < gButtons[i].y + gButtons[i].h)
			{
				currentStates[i] = MOUSE_OVER;
			}
			else
			{
				currentStates[i] = MOUSE_OUT;
			}
		}
	}
}
