#include<iostream>
#include"SDL.h"
#include "myTexture.h"
#include "Map.h"
#include "SDL_Image.h"
#include "Blood.h"
using namespace std;
extern int money;
extern int HP;
Blood::Blood(){}
Blood::Blood(double health) {
	maxHP = health;
	HPrate = 1;
}
double Blood::getHPrate() {
	return HPrate;
}
void Blood::attacked(const int& health) {
	if(maxHP>0)	HPrate = health / maxHP ;
}
