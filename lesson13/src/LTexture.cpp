#include "LTexture.h"
#include <SDL_image.h>
#include <stdio.h>

extern SDL_Renderer *gRenderer;

LTexture::LTexture()
{
	mTexture = NULL;
	width = height = 0;
	//ctor
}

LTexture::~LTexture()
{
	free();
	//dtor
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

bool LTexture::loadFromFile(std::string path)
{
	SDL_Surface *newSurface = NULL;
	SDL_Texture *newTexture = NULL;
	free();
	newSurface = IMG_Load(path.c_str());
	if(newSurface == NULL)
	{
		printf("img load failed for %s error %s\n", path.c_str(), IMG_GetError());
		return false;
	}

	newTexture = SDL_CreateTextureFromSurface(gRenderer, newSurface);
	if(newTexture == NULL)
	{
		printf("createTexture failed for %s error %s\n", path.c_str(), SDL_GetError());
		SDL_FreeSurface(newSurface);
		return false;
	}
	width = newSurface->w;
	height = newSurface->h;
	SDL_FreeSurface(newSurface);
	mTexture = newTexture;

	return true;
}

void LTexture::setColorMod(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(mTexture, r, g, b);
}

void LTexture::setBlendMode(SDL_BlendMode blend)
{
	SDL_SetTextureBlendMode(mTexture, SDL_BLENDMODE_BLEND);
}

void LTexture::setAlphaMod(Uint8 a)
{
	SDL_SetTextureAlphaMod(mTexture, a);
}

void LTexture::render(int x, int y, SDL_Rect *source)
{
	SDL_Rect dest{x, y, width, height};
	if(source != NULL)
	{
		dest.w = source->w;
		dest.h = source->h;
	}

	SDL_RenderCopy(gRenderer, mTexture, source, &dest);
}

int LTexture::getHeight()
{
	return height;
}

int LTexture::getWidth()
{
	return width;
}
