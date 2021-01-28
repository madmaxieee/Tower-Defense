#include "Cover.h"
#include "gameState.h"
#include "SDL_Mixer.h"

extern gameState STATE;
extern Mix_Music* gameBGM;
extern Mix_Music* coverBGM;

StartButton::StartButton() : myButton(2, "img/StartGame.png") {

}

bool StartButton::handleEvent(SDL_Event* event) {
	SDL_EventType event_type = myButton::handleEvent(event);
	switch (event_type) {
	case SDL_MOUSEMOTION:
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (STATE == MAIN_MENU) {
			STATE = PLAY;
			Mix_FreeMusic(coverBGM);
			Mix_PlayMusic(gameBGM, -1);
			return true;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		break;
	default:
		break;
	}
	return false;
}

Cover::Cover() : myWindow("img/cover.png") {

}

void Cover::render() {
	setPos(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	myWindow::render();
	SDL_Rect dstRect = {SCREEN_WIDTH / 2 - start_button.getmPosition().w / 2, SCREEN_HEIGHT * 3 / 4,
		start_button.getmPosition().w, start_button.getmPosition().h };
	start_button.render(&dstRect);
}

bool Cover::handleEvent(SDL_Event* event) {
	return start_button.handleEvent(event);
}