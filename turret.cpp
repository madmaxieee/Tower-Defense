#include "turret.h"
#include "cmath"
#include "myTexture.h"
#include "myTimer.h"
#include <iostream>
#include <cmath>
extern const int SCREEN_WIDTH, SCREEN_HEIGHT;
extern myTimer timer;
static const int BLOCK_WIDTH = (SCREEN_WIDTH - 80) / 15, BLOCK_HEIGHT = (SCREEN_HEIGHT - 80) / 10;

const double AttackR_data[5] = { 200,600,200,200,200 };
const double AttackS_data[5] = { 300 , 700, 500 , 200, 200 };
const int upgrade_interval[5] = { 75,150,100,100,100 };
extern myTexture snipTexture[4];
extern myTexture fireT_Texture[4];
extern myTexture avgTexture[4];
extern myTexture bullet_textures[5];
//extern void close_turret();
void extern Load_Turret();
void extern Load_Bullet();
//SDL_Window* gWindow = NULL;
//SDL_Renderer* gRenderer;
//The window renderer
//turret texture array
extern myTexture* turret_textures[5];
turret::turret() {}
turret::~turret() {
}
turret::turret(int x, int y) {
	builtTime = timer.getTicks();
	level = 0;
	Lockedup = false;
	place.x = x;
	place.y = y;
	place.w = BLOCK_WIDTH;
	place.h = BLOCK_HEIGHT;
	bulletCount = 0;
	lastTime = 0;
}

bool turret::sensor(Monster& m) {
	//need to moddify if combine
	double Distance;
	if (Lockedup == false) {
		Distance = sqrt((m.getCurrentClip().x + m.getCurrentClip().w / 2 - place.x - place.w / 2) * (m.getCurrentClip().x + m.getCurrentClip().w / 2 - place.x - place.w / 2) +
			(m.getCurrentClip().y + m.getCurrentClip().h / 2 - place.y - place.h / 2) * (m.getCurrentClip().y + m.getCurrentClip().h / 2 - place.y / 2));
		if (Distance < attack_range) {
			Lockedup = true;
			target = &m;
		}
	}
	else {
		if (target->getAlive() == true) {
			Distance = sqrt((target->getCurrentClip().x + target->getCurrentClip().w / 2 - place.x - place.w / 2) * (target->getCurrentClip().x +
				target->getCurrentClip().w / 2 - place.x - place.w / 2) + (target->getCurrentClip().y + target->getCurrentClip().h / 2
					- place.y - place.h / 2) * (target->getCurrentClip().y + m.getCurrentClip().h / 2 - place.y - place.h / 2));
			if (Distance > attack_range) {
				Lockedup = false;
				target = NULL;
			}
			else {
				//Questioned syntax
				attack(*target);
			}
		}
		else {
			Lockedup = false;
			return true;
		}

		rotate();
	}

	return true;
}
bool turret::getL() const {
	return Lockedup;
}

void turret::rotate() {
	if (target != NULL) {
		double sin = (target->getCurrentClip().x + target->getCurrentClip().w / 2 - place.x - place.w / 2) / sqrt((target->getCurrentClip().x + target->getCurrentClip().w / 2 - place.x - place.w / 2) *
			(target->getCurrentClip().x + target->getCurrentClip().w / 2 - place.x - place.w / 2) + (target->getCurrentClip().y + target->getCurrentClip().h / 2 - place.y - place.h / 2) *
			(target->getCurrentClip().y + target->getCurrentClip().h / 2 - place.y - place.h / 2));
		double check = (target->getCurrentClip().y + target->getCurrentClip().h / 2 - place.y - place.h / 2);
		direction = 360 * asin(sin) / (2 * M_PI);
		if (check > 0)
			direction = -direction + 180;

	}
}
//avarage  tower part
average_T::average_T() {}
average_T::average_T(int x, int y) :turret(x, y) {
	attack_speed = AttackS_data[0];
	attack_range = AttackR_data[0];
	attackmode = Ground;
	for (int i = 0; i < 10; i++)
		AllBullet[i] = NULL;
}
bool average_T::attack(Monster& m) {
	if (SDL_GetTicks() - lastTime > attack_speed) {
		AllBullet[bulletCount] = new average_B(place, m);
		bulletCount++;
		lastTime = SDL_GetTicks();
		if (bulletCount == 10) {
			delete AllBullet[0];
			AllBullet[0] = NULL;
			bulletCount = 0;
		}
		return true;
	}
	return false;
}

average_T::~average_T() {
}

void average_T::Upgrade() {
	if (level < 2) {
		level++;
		attack_speed -= upgrade_interval[0];
	}
}
void average_T::render() {
	if (timer.getTicks()- builtTime >= 20000 ) {
		builtTime = timer.getTicks();
		Upgrade();
	}
	avgTexture[level].render(NULL, &place, direction, NULL, SDL_FLIP_NONE);
	for (int i = 0; i < 10; i++) {
		if (AllBullet[i] != NULL && AllBullet[i]->getComplete() == true) {
			delete AllBullet[i];
			AllBullet[i] = NULL;
		}
		if (AllBullet[i] != NULL)
			AllBullet[i]->render();
	}
}
//sniper part
sniper::sniper() {

}

sniper::sniper(int x, int y) :turret(x, y) {
	attack_speed = AttackS_data[1];
	attack_range = AttackR_data[1];
	attackmode = Ground;
	for (int i = 0; i < 10; i++)
		AllBullet[i] = NULL;
}
bool sniper::attack(Monster& m) {
	if (SDL_GetTicks() - lastTime > attack_speed) {
		AllBullet[bulletCount] = new snip_B(place, m);
		bulletCount++;
		lastTime = SDL_GetTicks();
		if (bulletCount == 10) {
			delete AllBullet[0];
			AllBullet[0] = NULL;
			bulletCount = 0;
		}
		return true;
	}
	return false;
}
void sniper::Upgrade() {
	if (level < 2) {
		level++;
		attack_speed += 50;
	}
}
sniper::~sniper() {
}

void sniper::render() {
	if (timer.getTicks() - builtTime >= 20000 ) {
		builtTime = timer.getTicks();
		Upgrade();
	}
	snipTexture[level].render(NULL, &place, direction, NULL, SDL_FLIP_NONE);
	for (int i = 0; i < 10; i++) {
		if (AllBullet[i] != NULL && AllBullet[i]->getComplete() == true) {
			delete AllBullet[i];
			AllBullet[i] = NULL;
		}
		if (AllBullet[i] != NULL)
			AllBullet[i]->render();
	}
}
//fire
fire::fire() {}
fire::fire(int x, int y) :turret(x, y) {
	attack_speed = AttackS_data[2];
	attack_range = AttackR_data[2];
	attackmode = Ground;
	for (int i = 0; i < 10; i++)
		AllBullet[i] = NULL;
}
bool fire::attack(Monster& m) {
	if (SDL_GetTicks() - lastTime > attack_speed) {
		AllBullet[bulletCount] = new fire_B(place, m);
		bulletCount++;
		lastTime = SDL_GetTicks();
		if (bulletCount == 20) {
			delete AllBullet[0];
			AllBullet[0] = NULL;
			bulletCount = 0;
		}
		return true;
	}
	return false;
}
void fire::Upgrade() {
	if (level < 2) {
		level++;
		attack_speed += 50;
	}
}

fire::~fire() {
}

void fire::render() {
	if (timer.getTicks() - builtTime >= 20000) {
		builtTime = timer.getTicks();
		Upgrade();
	}

	fireT_Texture[level].render(NULL, &place, direction, NULL, SDL_FLIP_NONE);
	for (int i = 0; i < 20; i++) {
		if (AllBullet[i] != NULL && AllBullet[i]->getComplete() == true) {
			delete AllBullet[i];
			AllBullet[i] = NULL;
		}
		if (AllBullet[i] != NULL) {
			AllBullet[i]->render();
		}
	}
}
void fire::sensor(Monster& m) {
	turret::sensor(m);
	for (int i = 0; i < 20; i++) {
		if (AllBullet[i] != NULL)
			AllBullet[i]->burn(m);
	}
}