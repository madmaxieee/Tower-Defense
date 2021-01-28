#pragma once
#include<iostream>
#include"SDL.h"
#include "myTexture.h"
#include "Map.h"
#include "SDL_Image.h"
using namespace std;
extern int money;
extern int HP;
class Blood {
private:
	double HPrate;
	double maxHP;
public:
	Blood();
	Blood(double health);
	double getHPrate();
	void attacked(const int& health);
};
