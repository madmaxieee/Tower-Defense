#include "pause_menu.h"
#include <iostream>
#include "gameState.h"

extern gameState STATE;

PauseButton::PauseButton() : myButton(1, "img/gui/btn/pause.png") {

}

SDL_EventType PauseButton::handleEvent(SDL_Event* event) {
	SDL_EventType event_type = myButton::handleEvent(event);
	switch (event_type) {
	case SDL_MOUSEMOTION:
		break;
	case SDL_MOUSEBUTTONDOWN:
		if(STATE == PLAY)
			STATE = PAUSE;
		//SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x55);
		//SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
		//SDL_RenderFillRect(gRenderer, NULL);
		break;
	case SDL_MOUSEBUTTONUP:
		break;
	default:
		break;
	}
	return event_type;
}

void PauseButton::render() {
	SDL_Rect dstRect = {SCREEN_WIDTH - 40 - 5, 5, 40, 40};
	myButton::render(&dstRect);
}

SDL_EventType ContinueButton::handleEvent(SDL_Event* event) {
	SDL_EventType event_type = myButton::handleEvent(event);
	switch (event_type) {
	case SDL_MOUSEMOTION:
		break;
	case SDL_MOUSEBUTTONDOWN:
		if(STATE == PAUSE)
			STATE = PLAY;
		break;
	case SDL_MOUSEBUTTONUP:
		break;
	default:
		break;
	}
	return event_type;
}

PauseMenu::PauseMenu() : myWindow("img/gui/pause/bg.png") {
	restart = myButton(1, "img/gui/btn/restart.png");
	settings = myButton(1, "img/gui/btn/settings.png");
}

void PauseMenu::render() {
	myWindow::render();
	SDL_Rect dstRect = {SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT / 2 - 40, 80, 80};
	continue_playing.render(&dstRect);
	dstRect = { SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 - 40, 80, 80 };
	restart.render(&dstRect);
	dstRect = { SCREEN_WIDTH / 2 + 80, SCREEN_HEIGHT / 2 - 40, 80, 80 };
	settings.render(&dstRect);
}

void PauseMenu::handleEvent(SDL_Event* event) {
	continue_playing.handleEvent(event);
}

