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
