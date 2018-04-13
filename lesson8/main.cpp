#include <stdio.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

bool init();
void close();

int main(int argc, char *argv[])
{
	bool quit = false;
	SDL_Event e;

	SDL_Rect position;
	position.h = 80;
	position.w = 80;
	position.x = SCREEN_WIDTH / 2;
	position.y = SCREEN_HEIGHT / 2;

	if(!init())
	{
		printf("init failed\n");
		close();
		return 0;
	}

	while(!quit)
	{
		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(gRenderer);
		SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);
		SDL_RenderFillRect(gRenderer, &position);
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
					case SDLK_ESCAPE:
						quit = true;
						break;
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
		printf("SDL init failed error %s\n", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("sdl tutorial 8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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

void close()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();
}
