#include <iostream>
#include "Map.h"
#include "myTexture.h"
#include "gameState.h"
#include "turret.h"

using std::cout;

extern gameState STATE;
extern std::vector<turret*> turrets;

Pos::Pos() {
	x = 0;
	y = 0;
}

Pos::Pos(int x, int y) {
	this->x = x;
	this->y = y;
}

Pos::~Pos() {

}

// for reversed coordinates in map location
int Pos::getX() const {
	return y;
}
int Pos::getY() const {
	return x;
}

ostream& operator<< (ostream& output, const Pos m) {
	output << '(' << m.getX() << ", " << m.getY() << ')' << '\n';
	return output;
}

//BuildAvg
BuildAvg::BuildAvg() : myButton(2, "img/turrets/avgButton.png"){

}

void BuildAvg::handleEvent(SDL_Event* event, Pos pos) {
	SDL_EventType event_type = myButton::handleEvent(event);
	switch (event_type) {
	case SDL_MOUSEMOTION:
		break;
	case SDL_MOUSEBUTTONDOWN:

		break;
	case SDL_MOUSEBUTTONUP:
		if (STATE == BUILD_TURRET && last_event != SDL_MOUSEBUTTONUP) {
			average_T* tempAvg = new average_T(pos.x, pos.y);
			turrets.push_back(tempAvg);
			STATE = PLAY;
		}
		break;
	default:
		break;
	}
	last_event = event_type;
}

//BuildSnp
BuildSnp::BuildSnp() : myButton(2, "img/turrets/snpButton.png") {

}

void BuildSnp::handleEvent(SDL_Event* event, Pos pos) {
	SDL_EventType event_type = myButton::handleEvent(event);
	switch (event_type) {
	case SDL_MOUSEMOTION:
		break;
	case SDL_MOUSEBUTTONDOWN:
		break;
	case SDL_MOUSEBUTTONUP:
		if (STATE == BUILD_TURRET && last_event != SDL_MOUSEBUTTONUP) {
			sniper* tempSnp = new sniper(pos.x, pos.y);
			turrets.push_back(tempSnp);
			STATE = PLAY;
		}
		break;
	default:
		break;
	}
	last_event = event_type;
}

//BuildFire
BuildFire::BuildFire() : myButton(2, "img/turrets/fireButton.png") {

}

void BuildFire::handleEvent(SDL_Event* event, Pos pos) {
	SDL_EventType event_type = myButton::handleEvent(event);
	switch (event_type) {
	case SDL_MOUSEMOTION:
		break;
	case SDL_MOUSEBUTTONDOWN:

		break;
	case SDL_MOUSEBUTTONUP:
		if (STATE == BUILD_TURRET && last_event != SDL_MOUSEBUTTONUP) {
			fire* tempFire = new fire(pos.x, pos.y);
			turrets.push_back(tempFire);
			STATE = PLAY;
		}
		break;
	default:
		break;
	}
	last_event = event_type;
}

CloseMenu::CloseMenu() : myButton(1, "img/gui/btn/close_2.png") {

}

bool CloseMenu::handleEvent(SDL_Event* event) {
	SDL_EventType event_type = myButton::handleEvent(event);
	switch (event_type) {
	case SDL_MOUSEMOTION:
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (STATE == BUILD_TURRET && last_event != SDL_MOUSEBUTTONUP) {
			STATE = PLAY;
			return true;
		}
		break;
	case SDL_MOUSEBUTTONUP:
		break;
	default:
		break;
	}
	last_event = event_type;
	return false;
}

//TurretMenu
TurretMenu::TurretMenu() : myWindow("img/gui/pause/bg.png") {

}

bool TurretMenu::handleEvent(SDL_Event* event) {
	build_avg.handleEvent(event, pos);
	build_sniper.handleEvent(event, pos);
	build_fire.handleEvent(event, pos);
	return !close_menu.handleEvent(event);
}

void TurretMenu::render() {
	myWindow::render();
	SDL_Rect dstRect = { SCREEN_WIDTH / 2 - 160, SCREEN_HEIGHT / 2 - 40, 80, 80 };
	build_avg.render(&dstRect);
	dstRect = { SCREEN_WIDTH / 2 - 40, SCREEN_HEIGHT / 2 - 40, 80, 80 };
	build_sniper.render(&dstRect);
	dstRect = { SCREEN_WIDTH / 2 + 80, SCREEN_HEIGHT / 2 - 40, 80, 80 };
	build_fire.render(&dstRect);
	dstRect = { SCREEN_WIDTH  * 3 / 4 - 80, SCREEN_HEIGHT / 4 + 10, 50, 50 };
	close_menu.render(&dstRect);
}

TurretButton::TurretButton() : myButton(2, "img/turretBaseButtonSprite.png") {
	built = false;
}

TurretButton::~TurretButton() {
	myButton::~myButton();
}

Pos TurretButton::handleEvent(SDL_Event* event) {
	SDL_EventType event_type = myButton::handleEvent(event);
	Pos temp;
	switch (event_type) {
	case SDL_MOUSEMOTION:
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (STATE == PLAY && last_event != SDL_MOUSEBUTTONDOWN) {
			if (!built) {
				STATE = BUILD_TURRET;
				temp = Pos(mPosition.x, mPosition.y);
			}
			Sleep(200);
		}
		break;
	case SDL_MOUSEBUTTONUP:
		break;
	case BUILD_TURRET:
		break;
	default:
		break;
	}
	last_event = event_type;
	return temp;
}

Map::Map() :HEIGHT(10), WIDTH(15) {
	index = -1;
	map = new int* [HEIGHT];
	for (int i = 0; i < HEIGHT; i++) {
		map[i] = new int[WIDTH];
		for (int j = 0; j < WIDTH; j++) {
			map[i][j] = 0;
		}
	}
}

Map::Map(int idx) {
	index = idx;
	HEIGHT = 0;
	WIDTH = 0;
	map = NULL;
	BaseCount = 0;
	int k = 0;

	int map0[10][15] = {
	{0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 2, 0},
	{0, 2, 1, 2, 0, 2, 2, 2, 2, 2, 1, 2, 1, 2, 0},
	{0, 2, 1, 2, 0, 2, 1, 1, 1, 2, 1, 2, 1, 2, 0},
	{0, 2, 1, 2, 0, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0},
	{0, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0},
	{0, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0},
	{0, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 0},
	{0, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 2, 1, 2, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 4, 0, 0}
	};

	int map1[10][15] = {
	{0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0},
	{0, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0},
	{0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0},
	{0, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 0, 0, 0},
	{0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 0},
	{0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 0},
	{0, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 0},
	{0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 0},
	{0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0}
	};

	switch (idx) {
	case 0:
		title = "The Village";
		HEIGHT = 10;
		WIDTH = 15;
		BaseCount = 56;
		turretBases = new TurretButton * [BaseCount];
		//turretBases = new myButton*[BaseCount];
		map = new int* [HEIGHT];
		for (int i = 0; i < HEIGHT; i++) {
			map[i] = new int[WIDTH];
			for (int j = 0; j < WIDTH; j++) {
				if ((map[i][j] = map0[i][j]) == 2) {
					turretBases[k] = new TurretButton;
					//turretBases[k] = new myButton(2, "img/turretBaseButtonSprite.png");
					k++;
				}
			}
		}
		entry = Pos(0, 2);
		home = Pos(9, 12);
		return;
		break;
	case 1:title = "The Forest";
		HEIGHT = 10;
		WIDTH = 15;
		BaseCount = 56;
		turretBases = new TurretButton * [BaseCount];
		//turretBases = new myButton*[BaseCount];
		map = new int* [HEIGHT];
		for (int i = 0; i < HEIGHT; i++) {
			map[i] = new int[WIDTH];
			for (int j = 0; j < WIDTH; j++) {
				if ((map[i][j] = map1[i][j]) == 2) {
					turretBases[k] = new TurretButton;
					//turretBases[k] = new myButton(2, "img/turretBaseButtonSprite.png");
					k++;
				}
			}
		}
		entry = Pos(0, 2);
		home = Pos(9, 12);
		return;
		break;
		
	default:
		cout << "Please enter a number between 0 and 1.\n";
		return;
	}
}

Map::~Map() {
	int k = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (map[i][j] == 2) {
				turretBases[k]->~TurretButton();
				delete turretBases[k];
				k++;
			}
		}
	}
	for (int i = 0; i < HEIGHT; i++) {
		delete[] map[i];
	}
	delete[] map;
}

Map::Map(const Map& m) {
	title = m.title;
	WIDTH = m.WIDTH;
	HEIGHT = m.HEIGHT;
	entry = m.entry;
	home = m.home;
	BaseCount = m.BaseCount;
	index = m.index;
	int k;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			map[i][j] = m.map[i][j];
			if (map[i][j] == 2) {
				turretBases[k] = m.turretBases[k];
				k++;
			}
		}
	}
}

void operator++ (Map m) {
	Map temp(m.index + 1);
	m.~Map();
	m = temp;
}

int** Map::getMap() const {
	return map;
}

string Map::getTitle() const {
	return title;
}

Pos Map::getEntry() const {
	return entry;
}

Pos Map::getHome() const {
	return home;
}

int Map::getHeight() const {
	return HEIGHT;
}

int Map::getWidth() const {
	return WIDTH;
}

int Map::getBaseCount() const {
	return BaseCount;
}

ostream& operator<< (ostream& output, const Map m) {
	output << m.title << '\n';
	output << "\nHEIGHT = " << m.HEIGHT << '\n';
	output << " WIDTH = " << m.WIDTH << '\n';
	for (int i = 0; i < m.HEIGHT; i++) {
		for (int j = 0; j < m.WIDTH; j++) {
			output << m.map[i][j] << ((j < m.WIDTH - 1) ? " " : "");
		}
		output << '\n';
	}
	output << '\n';
	return output;
}

void Map::render(myTexture& nothingTexture, myTexture& roadTexture, myTexture& homeTexture) const {
	SDL_Rect currentDstRect;

	// counter for buttons
	int k = 0;

	for (int i = 0; i < this->getHeight(); i++) {
		for (int j = 0; j < this->getWidth(); j++) {
			currentDstRect.x = ((SCREEN_WIDTH - 80) / this->getWidth()) * j + 40;
			currentDstRect.y = ((SCREEN_HEIGHT - 80) / this->getHeight()) * i + 40;
			currentDstRect.w = (SCREEN_WIDTH - 80) / this->getWidth();
			currentDstRect.h = (SCREEN_HEIGHT - 80) / this->getHeight();

			//Render texture to screen
			switch (this->getMap()[i][j]) {
			case 0:
				nothingTexture.render(NULL, &currentDstRect);
				break;
			case 1:
				roadTexture.render(NULL, &currentDstRect);
				break;
			case 2:
				if (k < getBaseCount()) {
					turretBases[k]->render(&currentDstRect);
					k++;
				}
				break;
			case 3:
			case 4:
				homeTexture.render(NULL, &currentDstRect);
				break;
			}
		}
	}
}

SDL_Rect Map::getScreenPos(int x, int y) const {
	SDL_Rect rtnRect;
	rtnRect.x = ((SCREEN_WIDTH - 80) / this->getWidth()) * x + 40;
	rtnRect.y = ((SCREEN_HEIGHT - 80) / this->getHeight()) * y + 40;
	rtnRect.w = (SCREEN_WIDTH - 80) / this->getWidth();
	rtnRect.h = (SCREEN_HEIGHT - 80) / this->getHeight();
	return rtnRect;
}

Pos Map::handleEvent(SDL_Event* event, Pos build_target) {
	Pos temp, output;
	for (int i = 0; i < getBaseCount(); i++) {
		//if (turretBases[i]->getmPosition().x == build_target.x && turretBases[i]->getmPosition().y == build_target.y)
		//	turretBases[i]->built = true;
		temp = turretBases[i]->handleEvent(event);
		if (temp.x != 0) output = temp;
	}
	return output;
}