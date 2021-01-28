#pragma once

#include "myTexture.h"
#include "myButton.h"
#include "string"
#include <vector>

class myWindow {
	//�x�s�I��texture
	myTexture bg_texture;

	//�x�s���Dtexture
	myTexture heading_texture;

protected:
	//������m
	SDL_Rect pos;
	
	//���D��m
	SDL_Rect heading_pos;

public:
	bool enabled;
	// \param path1: path to background
	// \param path2: path to heading, can be omitted
	myWindow(std::string path1, std::string path2 = "");
	void render();
	void setPos(int x, int y, int w, int h);
};
