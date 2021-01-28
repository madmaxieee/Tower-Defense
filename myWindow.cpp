#include "myWindow.h"
#include <iostream>

extern SDL_Renderer* gRenderer;

myWindow::myWindow(std::string path1, std::string path2) {
	enabled = false;
	bg_texture.loadFromFile(path1);
	pos = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	heading_pos = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 8 };
	if (path2 != "") {
		heading_texture.loadFromFile(path2);
	}
	else {
		heading_texture.blank();
	}
}

void myWindow::render() {
	bg_texture.render(NULL, &pos);
	heading_texture.render(NULL, &heading_pos);
}

void myWindow::setPos(int x, int y, int w, int h) {
	pos = {x, y, w, h};
}