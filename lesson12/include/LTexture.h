#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL.h>
#include <string>
#include <stdio.h>
#include <SDL_image.h>

class LTexture
{
	public:
		LTexture();
		virtual ~LTexture();
		void free();
		bool loadFromFile(std::string path);
		void setColor(Uint8 r, Uint8 g, Uint8 b);
		void render(int x, int y, SDL_Rect *source);
		int getWidth();
		int getHeight();

	protected:

	private:
		int width;
		int height;
		SDL_Texture *mTexture;
};

#endif // LTEXTURE_H
