#pragma once

#include "myTexture.h"
#include "myButton.h"
#include "string"
#include <vector>

class myWindow {
	//儲存背景texture
	myTexture bg_texture;

	//儲存標題texture
	myTexture heading_texture;

protected:
	//視窗位置
	SDL_Rect pos;
	
	//標題位置
	SDL_Rect heading_pos;

public:
	bool enabled;
	// \param path1: path to background
	// \param path2: path to heading, can be omitted
	myWindow(std::string path1, std::string path2 = "");
	void render();
	void setPos(int x, int y, int w, int h);
};
