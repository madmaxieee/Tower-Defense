#include <string>
#include <iostream>
#include "myButton.h"

myButton::myButton(int states, std::string path)
{
	ButtonSpriteSheetTexture = new myTexture;
	ButtonSpriteSheetTexture->loadFromFile(path);
	BUTTON_STATES = states;
	mPosition = {0, 0, ButtonSpriteSheetTexture->getWidth(), ButtonSpriteSheetTexture->getHeight()};
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

	SpriteClips = new SDL_Rect[BUTTON_STATES];
	for (int i = 0; i < BUTTON_STATES; i++) {
		SpriteClips[i] = {i * (mPosition.w / BUTTON_STATES), 0,
			mPosition.w / BUTTON_STATES, mPosition.h};
	}
}

myButton::myButton() {
	
}

myButton::myButton(int states, myTexture* buttonTexture)
{
	ButtonSpriteSheetTexture = buttonTexture;
	mPosition = {0, 0, ButtonSpriteSheetTexture->getWidth(), ButtonSpriteSheetTexture->getHeight()};
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
	BUTTON_STATES = states;

	SpriteClips = new SDL_Rect[BUTTON_STATES];
	for (int i = 0; i < BUTTON_STATES; i++) {
		SpriteClips[i] = {i * (mPosition.w / BUTTON_STATES), 0,
			mPosition.w / BUTTON_STATES, mPosition.h};
	}
}

myButton::myButton(const myButton& button) {
	ButtonSpriteSheetTexture = button.ButtonSpriteSheetTexture;
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
	SpriteClips = button.SpriteClips;
	BUTTON_STATES = button.BUTTON_STATES;
	mPosition = button.mPosition;
	last_event = SDL_FIRSTEVENT;
}

myButton::~myButton() {
	delete[] SpriteClips;
	ButtonSpriteSheetTexture->~myTexture();
}

void myButton::setPosition(int x, int y, int w, int h)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.w = w;
	mPosition.h = h;
}

SDL_EventType myButton::handleEvent(SDL_Event* e)
{
	//If mouse event happened
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		bool inside = true;
		 
		//Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > mPosition.x + mPosition.w)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > mPosition.y + mPosition.h)
		{
			inside = false;
		}

		//Mouse is outside button
		if (!inside)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				return SDL_MOUSEMOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				return SDL_MOUSEBUTTONDOWN;
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				return SDL_MOUSEBUTTONUP;
				break;
			}
		}
	}
	return SDL_FIRSTEVENT;
}

//Show current button sprite
void myButton::render(SDL_Rect* dstRect)
{
	if (dstRect)
	{
		setPosition(dstRect->x, dstRect->y, dstRect->w, dstRect->h);
	}
	if (mCurrentSprite >= BUTTON_STATES) {
		ButtonSpriteSheetTexture->render(&SpriteClips[0], dstRect);
	}
	else if (mCurrentSprite >= 0){
		ButtonSpriteSheetTexture->render(&SpriteClips[mCurrentSprite], dstRect);
	}
}

SDL_Rect myButton::getmPosition() {
	return mPosition;
}