#include "LTexture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <stdio.h>

extern SDL_Renderer *gRenderer;
extern TTF_Font *gFont;

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
	free();

	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;

	surface = IMG_Load(path.c_str());
	if(surface == NULL)
	{
		printf("img load failed for %s error %s\n", path.c_str(), SDL_GetError());
		return false;
	}

	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 255));
	texture = SDL_CreateTextureFromSurface(gRenderer, surface);
	if(texture == NULL)
	{
		printf("createtexture failed %s error %s\n", path.c_str(), SDL_GetError());
		SDL_FreeSurface(surface);
		return false;
	}
	width = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);
	mTexture = texture;
	return true;
}

void LTexture::render(int x, int y, SDL_Rect *source, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	SDL_Rect dest{x, y, width, height};
	if(source != NULL)
	{
		dest.w = source->w;
		dest.h = source->h;
	}
	SDL_RenderCopyEx(gRenderer, mTexture, source, &dest, angle, center, flip);
}

int LTexture::getWidth()
{
	return width;
}

int LTexture::getHeight()
{
	return height;
}

bool LTexture::loadFromRenderedText(std::string text, SDL_Color *color)
{
	free();

	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;
	SDL_Color red{255, 0, 0, 255};
	SDL_Color blue{0, 0, 255, 0};

//	surface = TTF_RenderText_Solid(gFont, text.c_str(), *color);
	surface = TTF_RenderText_Shaded(gFont, text.c_str(), red, blue);
	if(surface == NULL)
	{
		printf("failed to renderText %s\n", TTF_GetError());
		return false;
	}

	texture = SDL_CreateTextureFromSurface(gRenderer, surface);
	if(texture == NULL)
	{
		printf("createtexture failed %s error %s\n", text.c_str(), SDL_GetError());
		SDL_FreeSurface(surface);
		return false;
	}
	width = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);
	mTexture = texture;
	return true;


}
