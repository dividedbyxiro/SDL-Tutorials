#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <string>
#include <SDL.h>

using namespace std;


class LTexture
{
	public:
		LTexture();
		~LTexture();
		bool loadFromFile(string path, SDL_Renderer *renderer);
		void free();
		void render(int x, int y, SDL_Renderer *renderer);
		int getWidth();
		int getHeight();

	protected:

	private:
		SDL_Texture *mTexture;
		int width;
		int height;
};

#endif // LTEXTURE_H
