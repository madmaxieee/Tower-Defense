#include "myTimer.h"

extern SDL_Renderer* gRenderer;

myTimer::myTimer()
{
	//Initialize the variables
	mStartTicks = 0;
	mPausedTicks = 0;

	mPaused = false;
	mStarted = false;

	textColor = {0x00, 0x00, 0x00, 0xFF};
	TextSize = 28;
}

void myTimer::start()
{
	//Start the timer
	mStarted = true;

	//Unpause the timer
	mPaused = false;

	//Get the current clock time
	mStartTicks = SDL_GetTicks();
	mPausedTicks = 0;
}

void myTimer::stop()
{
	//Stop the timer
	mStarted = false;

	//Unpause the timer
	mPaused = false;

	//Clear tick variables
	mStartTicks = 0;
	mPausedTicks = 0;
}

void myTimer::pause()
{
	//If the timer is running and isn't already paused
	if (mStarted && !mPaused)
	{
		//Pause the timer
		mPaused = true;

		//Calculate the paused ticks
		mPausedTicks = SDL_GetTicks() - mStartTicks;
		mStartTicks = 0;
	}
}

void myTimer::unpause()
{
	//If the timer is running and paused
	if (mStarted && mPaused)
	{
		//Unpause the timer
		mPaused = false;

		//Reset the starting ticks
		mStartTicks = SDL_GetTicks() - mPausedTicks;

		//Reset the paused ticks
		mPausedTicks = 0;
	}
}

Uint32 myTimer::getTicks()
{
	//The actual timer time
	Uint32 time = 0;

	//If the timer is running
	if (mStarted)
	{
		//If the timer is paused
		if (mPaused)
		{
			//Return the number of ticks when the timer was paused
			time = mPausedTicks;
		}
		else
		{
			//Return the current time minus the start time
			time = SDL_GetTicks() - mStartTicks;
		}
	}

	return time;
}

bool myTimer::isStarted()
{
	//Timer is running and paused or unpaused
	return mStarted;
}

bool myTimer::isPaused()
{
	//Timer is running and paused
	return mPaused && mStarted;
}

void myTimer::render() {
	std::stringstream timeText;
	timeText.str("");
	timeText << int(getTicks() / 1000) / 60 << ':';
	if (int(getTicks() / 1000) % 60 < 10) {
		timeText << '0';
	}
	timeText << int(getTicks() / 1000) % 60;

	TimeTexture.loadFromRenderedText(timeText.str().c_str(), textColor);

	SDL_Rect dstRect = { SCREEN_WIDTH - 80 - TimeTexture.getWidth() -5, 6 -5, TimeTexture.getWidth() +10, TextSize +10};
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0x55);
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(gRenderer, &dstRect);

	dstRect = { SCREEN_WIDTH - 80 - TimeTexture.getWidth(), 6, TimeTexture.getWidth(), TextSize};
	TimeTexture.render(NULL, &dstRect);
}
