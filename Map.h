#pragma once

#include <string>
#include <iostream>
#include "SDL.h"
#include "myTexture.h"
#include "myButton.h"
#include "myWindow.h"

using namespace std;

enum TurretType {
	NONE = 0,
	AVG = 1,
	SNP = 2,
	FIRE = 3
};

class Pos {
	friend ostream& operator<< (ostream& output, const Pos m);
public:
	int x;
	int y;
	// set as (0,0) by default
	Pos();

	Pos(int x, int y);
	~Pos();
	int getX() const;
	int getY() const;
};

class BuildAvg : public myButton {
public:
	BuildAvg();
	void handleEvent(SDL_Event* event, Pos pos);
};

class BuildSnp : public myButton {
public:
	BuildSnp();
	void handleEvent(SDL_Event* event, Pos pos);
};

class BuildFire : public myButton {
public:
	BuildFire();
	void handleEvent(SDL_Event* event, Pos pos);
};

class CloseMenu : public myButton {
public:
	CloseMenu();
	bool handleEvent(SDL_Event* event);
};

class TurretMenu : myWindow {
private:
	BuildAvg build_avg;
	BuildSnp build_sniper;
	BuildFire build_fire;
	CloseMenu close_menu;
public:
	Pos pos;
	TurretMenu();
	bool handleEvent(SDL_Event* event);
	void render();
};

class TurretButton : public myButton{
public:
	TurretButton();
	~TurretButton();
	Pos handleEvent(SDL_Event* event);
	bool built;
};

// 0: nothing, 1: road, 2: turret base, 3: start, 4: home
// call getMap() to get int** map
class Map {
	friend ostream& operator<< (ostream& output, const Map m);
	friend void operator++ (Map m);

private:
	string title;
	int WIDTH;
	int HEIGHT;
	Pos entry;
	Pos home;
	int** map;
	int BaseCount;
	int index;

public:
	TurretButton** turretBases;
	//myButton** turretBases;

	// creates a blank 10 * 15 map
	Map();

	// \brief create a new map with properties of already designed maps
	// start form 0
	Map(int idx);

	Map(const Map &m);

	~Map();

	int** getMap() const;
	string getTitle() const;
	Pos getEntry() const;
	Pos getHome() const;
	
	// \return the number of tiles vertically
	int getHeight() const;
	
	// \return the number of tiles horizontally
	int getWidth() const;
	
	int getBaseCount() const;
	void render(myTexture& nothingTexture, myTexture& roadTexture, myTexture& homeTexture) const;
	Pos handleEvent(SDL_Event* event, Pos build_target);

	// \brief return the position of a tile on screen
	// \param
	SDL_Rect getScreenPos(int y, int x) const;
};