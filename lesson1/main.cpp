#include <stdio.h>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gHelloWorld = NULL;

bool init();

bool loadMedia();

void close();

int main(int argc, char *argv[])
{
    if(!init())
	{
		printf("init failed\n");
		close();
		return 0;
	}

	if(!loadMedia())
	{
		printf("laod medai failed\n");
		close();
		return 0;
	}

	SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
	SDL_UpdateWindowSurface(gWindow);
	SDL_Delay(2000);
	close();
	return 0;
}

bool init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initiated error %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("SDL Tutorial 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL)
    {
        printf("SDL window could not be created %s\n", SDL_GetError());
        return false;
    }
    gScreenSurface = SDL_GetWindowSurface(gWindow);
    return true;
}

bool loadMedia()
{
    gHelloWorld = SDL_LoadBMP("../media/hello_world.bmp");
    if(gHelloWorld == NULL)
	{
		printf("unable to load hello world image%s\n", SDL_GetError());
		return false;
	}

	return true;
}

void close()
{
	SDL_DestroyWindow(gWindow);
	SDL_FreeSurface(gHelloWorld);
	gWindow = NULL;
	gHelloWorld = NULL;
	gScreenSurface = NULL;

	SDL_Quit();

}
