#include <stdio.h>
#include <SDL.h>
#include <string>



const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL;
SDL_Surface *gCurrentSurface = NULL;
SDL_Surface *gPress = NULL;
SDL_Surface *gUp = NULL;
SDL_Surface *gDown = NULL;
SDL_Surface *gLeft = NULL;
SDL_Surface *gRight = NULL;

bool init();
bool loadMedia();
void close();

SDL_Surface* loadSurface(std::string fileName);

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

	gCurrentSurface = gPress;

	while(!quit)
	{
		SDL_BlitSurface(gCurrentSurface, NULL, gSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);

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
					gCurrentSurface = gUp;
					break;
				case SDLK_DOWN:
					gCurrentSurface = gDown;
					break;
				case SDLK_LEFT:
					gCurrentSurface = gLeft;
					break;
				case SDLK_RIGHT:
					gCurrentSurface = gRight;
					break;
				case SDLK_q:
				case SDLK_ESCAPE:
					quit = true;
					break;
				default:
					gCurrentSurface = gPress;
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
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
	{
		printf("sdl init failed %s\n", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("SDL tutorial 4", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		printf("create window failed %s\n", SDL_GetError());
		return false;
	}
	gSurface = SDL_GetWindowSurface(gWindow);
	return true;
}

bool loadMedia()
{
	gPress = loadSurface("../media/press.bmp");
	if(gPress == NULL)
	{
		printf("press image failed to load\n");
		return false;
	}

	gUp = loadSurface("../media/up.bmp");
	if(gUp == NULL)
	{
		printf("up image failed to load\n");
		return false;
	}

	gDown = loadSurface("../media/down.bmp");
	if(gDown == NULL)
	{
		printf("down image failed to load\n");
		return false;
	}

	gLeft = loadSurface("../media/left.bmp");
	if(gLeft == NULL)
	{
		printf("left image failed to load\n");
		return false;
	}

	gRight = loadSurface("../media/right.bmp");
	if(gRight == NULL)
	{
		printf("right image failed to load\n");
		return false;
	}

	return true;
}

SDL_Surface* loadSurface(std::string fileName)
{
	SDL_Surface *ret = SDL_LoadBMP(fileName.c_str());
	if(ret == NULL)
	{
		printf("failed to load %s error %s\n", fileName.c_str(), SDL_GetError());
		return NULL;
	}
	return ret;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	SDL_FreeSurface(gSurface);
	SDL_FreeSurface(gCurrentSurface);
	SDL_FreeSurface(gPress);
	SDL_FreeSurface(gUp);
	SDL_FreeSurface(gDown);
	SDL_FreeSurface(gLeft);
	SDL_FreeSurface(gRight);
	gWindow = NULL;
	gSurface = gCurrentSurface = gPress = gUp = gDown = gLeft = gRight = NULL;
	SDL_Quit();
}
