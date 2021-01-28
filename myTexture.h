#pragma once

#include "SDL.h"
#include <SDL_ttf.h>
#include <string>

const int SCREEN_WIDTH = 1440;
const int SCREEN_HEIGHT = SCREEN_WIDTH * 9 / 16;

//Texture wrapper class
class myTexture
{
public:
	//Initializes variables
	myTexture();

	//Deallocates memory
	~myTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

#if defined(SDL_TTF_MAJOR_VERSION)
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	//SDL_BLENDMODE_BLEND
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	void blank();

	// \brief Renders texture at given point
	// \param srcRect: NULL by default (SDL_Rect*)
	// \param dstRect: Null by default (SDL_Rect*)
	// \param angle: for rotation, 0 by default
	// \param center: for rotation, NULL by default (SDL_Point*)
	// \param flip: (SDL_RendererFlip), none by default
	void render(SDL_Rect* srcRect = NULL, SDL_Rect* dstRect = NULL, double angle = 0.0,
				SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	//Image dimensions
	int mWidth;
	int mHeight;
};