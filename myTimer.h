#pragma once
#include <string>
#include <sstream>
#include <SDL_ttf.h>
#include "myTexture.h"

class myTimer
{
public:
	//Initializes variables
	myTimer();

	myTexture TimeTexture;
	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	Uint32 getTicks();

	//Checks the status of the timer
	bool isStarted();
	bool isPaused();

	void render();

	SDL_Color textColor;

private:
	//The clock time when the timer started
	Uint32 mStartTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//The timer status
	bool mPaused;
	bool mStarted;

	int TextSize;
};

