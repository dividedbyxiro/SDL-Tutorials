#include "LTexture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>


LTexture::LTexture()
{
	mTexture = NULL;
	width = height = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile(string path, SDL_Renderer *renderer)
{
	SDL_Texture *newTexture;
	SDL_Surface *newSurface;

	free();

	newSurface = IMG_Load(path.c_str());
	if(newSurface == NULL)
	{
		printf("failed to load image %s error %s\n", path.c_str(), IMG_GetError());
		return false;
	}
	SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, 0, 255, 255));
	newTexture = SDL_CreateTextureFromSurface(renderer, newSurface);
	if(newTexture == NULL)
	{
		printf("failed to create texture from surface %s error %s\n", path.c_str(), SDL_GetError());
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

void LTexture::render(int x, int y, SDL_Renderer *renderer)
{
	SDL_Rect dest = {x, y, width, height};
	SDL_RenderCopy(renderer, mTexture, NULL, &dest);
}

int LTexture::getHeight()
{
	return height;
}

int LTexture::getWidth()
{
	return width;
}
