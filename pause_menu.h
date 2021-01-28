#pragma once
#include "SDL.h"
#include "myTexture.h"
#include "myButton.h"
#include "myWindow.h"
#include "string"
#include <vector>



class PauseButton : public myButton {
public:
	PauseButton();
	SDL_EventType handleEvent(SDL_Event* event);
	void render();
};

class ContinueButton : public myButton {
public:
	ContinueButton() : myButton(1, "img/gui/btn/play.png") {

	}
	SDL_EventType handleEvent(SDL_Event* event);
};

class PauseMenu : public myWindow {
	ContinueButton continue_playing;
	myButton restart;
	myButton settings;
public:
	PauseMenu();
	void render();
	void handleEvent(SDL_Event* event);
};
