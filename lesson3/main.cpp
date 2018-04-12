#include <stdio.h>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadMedia();
void close();

SDL_Window *gWindow = NULL;
SDL_Surface *gSurface = NULL;
SDL_Surface *gPrompt = NULL;

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
		SDL_BlitSurface(gPrompt, NULL, gSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);
		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT)
		{
			quit = true;
		}
		if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
		{
			quit = true;
		}

	}

	printf("thanks for playing\n");
	close();
	return 0;
}

/** Gets SDL ready for use
 * \param none
 * \return bool true if successful
 */
bool init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL init failed %s\n", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("SDL tutorial 3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(gWindow == NULL)
	{
		printf("failed to create window %s\n", SDL_GetError());
		return false;
	}
	gSurface = SDL_GetWindowSurface(gWindow);
	return true;
}



/** \brief loads media
 * \param none
 * \param still none
 * \return bool true if successful
 */
bool loadMedia()
{
	gPrompt = SDL_LoadBMP("../media/background.bmp");
	if(gPrompt == NULL)
	{
		printf("loadBMP failed %s\n", SDL_GetError());
		return false;
	}
	return true;


}


void close()
{
	SDL_DestroyWindow(gWindow);
	SDL_FreeSurface(gSurface);
	SDL_FreeSurface(gPrompt);
	gWindow = NULL;
	gSurface = NULL;
	gPrompt = NULL;
	SDL_Quit();

}
