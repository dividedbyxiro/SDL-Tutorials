#include "LTexture.h"
#include <stdio.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

extern SDL_Renderer *gRenderer;

LTexture::LTexture()
{
	mTexture = NULL;
	width = height = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile(string path)
{
	SDL_Surface *newSurface = NULL;
	SDL_Texture *newTexture = NULL;

	newSurface = IMG_Load(path.c_str());
	if(newSurface == NULL)
	{
		printf("img load failed %s error %s\n", path.c_str(), IMG_GetError());
		return false;
	}
	SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, 0, 255, 255));
	newTexture = SDL_CreateTextureFromSurface(gRenderer, newSurface);
	if(newTexture == NULL)
	{
		printf("createTexture failed %s error %s\n", path.c_str(), SDL_GetError());
		SDL_FreeSurface(newSurface);
		return false;
	}

	width = newSurface->w;
	height = newSurface->h;
	SDL_FreeSurface(newSurface);
	mTexture = newTexture;
	return true;
}

void LTexture::free()
{
	if(mTexture == NULL)
	{
		return;
	}
	SDL_DestroyTexture(mTexture);
	width = height = 0;
}

void LTexture::render(int x, int y, SDL_Rect* rect)
{
	SDL_Rect dest = {x, y, width, height};
	if(rect != NULL)
	{
		dest.w = rect->w;
		dest.h = rect->h;
	}

	SDL_RenderCopy(gRenderer, mTexture, rect, &dest);
}

int LTexture::getWidth()
{
	return width;
}

int LTexture::getHeight()
{
	return height;
}
