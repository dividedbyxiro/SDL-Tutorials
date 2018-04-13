#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using namespace std;

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gBackGround = NULL;
SDL_Texture *gTest = NULL;
SDL_Texture *gTurret = NULL;

bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture(string path);

int main(int argc, char *argv[])
{
	bool quit = false;
	SDL_Event e;

	SDL_Rect topLeft;
	topLeft .x = 0;
	topLeft.y = 0;
	topLeft.w = SCREEN_WIDTH / 2;
	topLeft.h = SCREEN_HEIGHT / 2;

	SDL_Rect topRight;
	topRight.x = SCREEN_WIDTH / 2;
	topRight.y = 0;
	topRight.w = SCREEN_WIDTH / 2;
	topRight.h = SCREEN_HEIGHT / 2;

	SDL_Rect bottom;
	bottom.x = 0;
	bottom.y = SCREEN_HEIGHT / 2;
	bottom.w = SCREEN_WIDTH;
	bottom.h = SCREEN_HEIGHT / 2;

	SDL_Rect position;
	position.x = SCREEN_WIDTH / 2;
	position.y = 50;
	position.w = position.h = 64;

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
		SDL_RenderSetViewport(gRenderer, &topLeft);
		SDL_RenderCopy(gRenderer, gBackGround, NULL, NULL);
		SDL_RenderSetViewport(gRenderer, &topRight);
		SDL_RenderCopy(gRenderer, gTest, NULL, NULL);
		SDL_RenderSetViewport(gRenderer, &bottom);
		SDL_RenderCopy(gRenderer, gBackGround, NULL, NULL);
//		SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
//		SDL_RenderFillRect(gRenderer, &position);
		SDL_RenderCopy(gRenderer, gTurret, NULL, &position);
		SDL_RenderPresent(gRenderer);

		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if(e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_UP:
						position.y -= 10;
						break;
					case SDLK_DOWN:
						position.y += 10;
						break;
					case SDLK_RIGHT:
						position.x += 10;
						break;
					case SDLK_LEFT:
						position.x -= 10;
						break;
					case SDLK_ESCAPE:
						quit = true;
						break;
				}
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

	gWindow = SDL_CreateWindow("sdl tutorial 9", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		printf("failed to create window %s\n", SDL_GetError());
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
	gBackGround = loadTexture("../media/background.png");
	if(gBackGround == NULL)
	{
		printf("failed to load background\n");
		return false;
	}

	gTest = loadTexture("../media/test.png");
	if(gTest == NULL)
	{
		printf("failed to load test\n");
		return false;
	}

	gTurret = loadTexture("../media/piskel turret.png");
	if(gTurret == NULL)
	{
		printf("failed to load turret\n");
		return false;
	}

	return true;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyTexture(gBackGround);
	SDL_DestroyTexture(gTest);
	SDL_DestroyTexture(gTurret);
	gWindow = NULL;
	gRenderer = NULL;
	gBackGround = gTest = gTurret = NULL;

	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture(string path)
{
	SDL_Surface *loadedSurface = NULL;
	SDL_Texture *newTexture = NULL;

	loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL)
	{
		printf("img load failed for %s error %s\n", path.c_str(), IMG_GetError());
		return NULL;
	}

	newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
	if(newTexture == NULL)
	{
		printf("failed to create texture from surface %s error %s\n", path.c_str(), SDL_GetError());
		SDL_FreeSurface(loadedSurface);
		return NULL;
	}

	SDL_FreeSurface(loadedSurface);
	return newTexture;
}
