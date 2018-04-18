#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <string>
#include <SDL.h>


class LTexture
{
	public:
		LTexture();
		virtual ~LTexture();
		void free();
		bool loadFromFile(std::string path);
		void setColorMod(Uint8 r, Uint8 g, Uint8 b);
		void setBlendMode(SDL_BlendMode blend);
		void setAlphaMod(Uint8 a);
		void render(int x, int y, SDL_Rect *source);
		int getWidth();
		int getHeight();

	protected:

	private:
		SDL_Texture *mTexture;
		int width;
		int height;
};

#endif // LTEXTURE_H
