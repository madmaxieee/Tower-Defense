#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "myTexture.h"
#include <Windows.h>

enum myButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
};

class myButton
{
	// 儲存按鈕 sprites
	myTexture* ButtonSpriteSheetTexture;

	// 現在使用的 sprite
	myButtonSprite mCurrentSprite;

	// sprite 的框框
	SDL_Rect* SpriteClips;

	// 按鈕總狀態數
	int BUTTON_STATES;

protected:
	// 按鈕在螢幕上的位子
	SDL_Rect mPosition;

	// 按鈕上一次handle的事件
	SDL_EventType last_event;

public:
	// \brief Initializes internal variables
	// \param button states [0: out, 1: over, 2: down, 3:up]
	// \param path
	myButton(int states, std::string path);

	// \brief Initializes internal variables
	// \param button states [0: out, 1: over, 2: down, 3:up]
	// \param buttonTexture (myTexture*)
	myButton(int states, myTexture* buttonTexture);

	myButton();

	myButton(const myButton& button);

	~myButton();

	//Sets top left position for in/out detection
	void setPosition(int x, int y, int w, int h);

	// \brief Handles mouse event
	// \return event type (SDL_MOUSEBUTTONUP, SDL_MOUSEBUTTONDOWN or SDL_MOUSEMOTION)
	SDL_EventType handleEvent(SDL_Event* e);

	//Shows button sprite
	void render(SDL_Rect* dstRect);

	SDL_Rect getmPosition();
};
