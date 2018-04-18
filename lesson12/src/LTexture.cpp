#include "LTexture.h"


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

void LTexture::free()
{
	if(mTexture == NULL)
	{
		return;
	}

	SDL_DestroyTexture(mTexture);
	width = height = 0;
}

void LTexture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(mTexture, r, g, b);
}

bool LTexture::loadFromFile(std::string path)
{
	SDL_Surface *surface = NULL;
	SDL_Texture *texture = NULL;
	surface = IMG_Load(path.c_str());
	if(surface == NULL)
	{
		printf("img load failed for %s error %s\n", path.c_str(), IMG_GetError());
		return false;
	}

	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 255));

	texture = SDL_CreateTextureFromSurface(gRenderer, surface);
	if(texture == NULL)
	{
		printf("createTexture failed for %s error %s\n", path.c_str(), SDL_GetError());
		SDL_FreeSurface(surface);
		return false;
	}


	width = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);
	mTexture = texture;
	return true;
}

int LTexture::getWidth()
{
	return width;
}

int LTexture::getHeight()
{
	return height;
}

void LTexture::render(int x, int y, SDL_Rect* source)
{
	SDL_Rect dest = {x, y, width, height};
	if(source != NULL)
	{
		dest.w = source->w;
		dest.h = source->h;
	}
	SDL_RenderCopy(gRenderer, mTexture, source, &dest);
}

