#include "LTexture.h"

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

LTexture gBackground;
LTexture gFoo;

bool init();
bool loadMedia();
void close();

int main(int argc, char *argv[])
{
	bool quit = false;
	SDL_Event e;

	Uint8 r = 255, g = 255, b = 255;

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
		gFoo.render(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, NULL);
		SDL_RenderPresent(gRenderer);

		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT)
		{
			quit = true;
		}
		r -= 1;
		g -= 2;
		b -= 3;
		gFoo.setColor(r, g, b);
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

	gWindow = SDL_CreateWindow("sdl tutorial 12", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		printf("createWindow failed error %s\n", SDL_GetError());
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(gRenderer == NULL)
	{
		printf("create renderer failed %s\n", SDL_GetError());
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

	if(!gFoo.loadFromFile("../media/foo.png"))
	{
		printf("failed to load foo\n");
		return false;
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
