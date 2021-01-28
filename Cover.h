#pragma once

#include "SDL.h"
#include "myTexture.h"
#include "myButton.h"
#include "myWindow.h"
#include "string"

class StartButton : public myButton {
public:
	StartButton();
	bool handleEvent(SDL_Event* event);
};

class Cover : public myWindow {
	StartButton start_button;
public:
	Cover();
	void render();
	bool handleEvent(SDL_Event* event);
};
