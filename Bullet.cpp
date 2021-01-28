#include "bullet.h"
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <cstdio>
#include<string>
#include "bullet.h"
#include "SDL_mixer.h"
std::string path;
static const int bullet_sizew=10,bullet_sizeh=10;
const int LTime=3000;
extern SDL_Renderer* gRenderer;
const double velocity_Data[3] = {6,20,6};
const int damage_Data[3] = {50,150,10};
const int Detect_area=15;
extern myTexture bullet_textures[5]; 
extern myTexture fireTextures[12];
extern int BLOCK_WIDTH;
extern int BLOCK_HEIGHT;
extern int BULID_FRAMES = 4;
extern Mix_Chunk* gHit;
extern Mix_Chunk* gburn;
//texture data of bullet
bullet::bullet(){}
bullet::bullet(SDL_Rect& pos_T, Monster& m) {
	target = &m;
	pos.w = bullet_sizew;
	pos.h = bullet_sizeh;
	pos.x = pos_T.x+pos_T.w/2;
	pos.y = pos_T.y+pos_T.h/2;
	exactX = pos_T.x+ pos_T.w / 2-pos.w/2;
	exactY = pos_T.y + pos_T.h / 2-pos.h/2;
	complete = false;

}
bullet::~bullet() {}
int bullet::getx() const {
	return pos.x;
}

int bullet::gety() const {
	return pos.y;
}
bool bullet::getComplete()  {
	return complete;
}
void bullet::move() {
	if (target->getAlive() == true) {
		if ((target->getCurrentClip().x + target->getCurrentClip().w / 2 - pos.x) * (target->getCurrentClip().x + target->getCurrentClip().w / 2 - pos.x) +
			(target->getCurrentClip().y + target->getCurrentClip().h / 2 - pos.y) * (target->getCurrentClip().y + target->getCurrentClip().h / 2 - pos.y)
			< Detect_area * Detect_area) {
			target->attacked(damage);
			Mix_PlayChannel(-1, gHit, 0);
			complete = true;
		}
		velocity_x = velocity * (target->getCurrentClip().x + target->getCurrentClip().w / 2 - pos.x) / sqrt((target->getCurrentClip().x + target->getCurrentClip().w / 2 - pos.x) *
			(target->getCurrentClip().x + target->getCurrentClip().w / 2 - pos.x) + (target->getCurrentClip().y + target->getCurrentClip().h / 2 - pos.y) * (target->getCurrentClip().y + target->getCurrentClip().h / 2 - pos.y));
		velocity_y = velocity * (target->getCurrentClip().y + target->getCurrentClip().h / 2 - pos.y) / sqrt((target->getCurrentClip().x + target->getCurrentClip().w / 2 - pos.x) *
			(target->getCurrentClip().x + target->getCurrentClip().w / 2 - pos.x) + (target->getCurrentClip().y + target->getCurrentClip().h / 2 - pos.y) * (target->getCurrentClip().y + target->getCurrentClip().h / 2 - pos.y));
		exactX += velocity_x;
		exactY += velocity_y;
		pos.x = (int)exactX;
		pos.y = (int)exactY;
	}
	else
		complete = true;
}
//average_B
average_B::average_B() {}
average_B::average_B(SDL_Rect& pos_T, Monster& m) :bullet(pos_T,m){
	velocity = velocity_Data[0];
	avgB_Texture = &bullet_textures[0];
	damage = damage_Data[0];
}
void average_B::render() {
	avgB_Texture->render(NULL, &pos, 0, NULL, SDL_FLIP_NONE);
	move();
}
//snip_B
snip_B::snip_B() {}
snip_B::snip_B(SDL_Rect& pos_T, Monster& m) :bullet(pos_T, m) {
	velocity = velocity_Data[1];
	snipB_Texture = &bullet_textures[1];
	damage = damage_Data[1];
}
void snip_B::render() {
	snipB_Texture->render(NULL, &pos, 0, NULL, SDL_FLIP_NONE);
	move();
}
//fire
fire_B::fire_B() {}
fire_B::fire_B(SDL_Rect& pos_T, Monster& m) :bullet(pos_T, m) {
	hit = false;
	velocity = velocity_Data[2];
	fireB_Texture = &bullet_textures[2];
	damage = damage_Data[2];
	LiveTime = LTime;
	hitTime = 0;
}
void fire_B::render() {
	if(hitTime!=0){
		fireB_Texture=&fireTextures[((SDL_GetTicks()-hitTime)/50)%12];
	}
	fireB_Texture->render(NULL, &pos, 0, NULL, SDL_FLIP_NONE);
	fire_B::move();
}
void fire_B::move() {
	if (target->getAlive() == true) {
		if (hit == false) {
			if ((target->getCurrentClip().x + target->getCurrentClip().w / 2 - pos.x) * (target->getCurrentClip().x + target->getCurrentClip().w / 2 - pos.x) +
				(target->getCurrentClip().y + target->getCurrentClip().h / 2 - pos.y) * (target->getCurrentClip().y + target->getCurrentClip().h / 2 - pos.y)
				< Detect_area * Detect_area) {
				target->attacked(damage);
				Mix_PlayChannel(-1, gburn, 0);
				hit = true;
				hitTime = SDL_GetTicks();
				pos.w = 30;
				pos.h = 30;
			}
			else {
				velocity_x = velocity * (target->getCurrentClip().x + target->getCurrentClip().w / 2 - pos.x) / sqrt((target->getCurrentClip().x + target->getCurrentClip().w / 2 - pos.x) *
					(target->getCurrentClip().x + target->getCurrentClip().w / 2 - pos.x) + (target->getCurrentClip().y + target->getCurrentClip().h / 2 - pos.y) * (target->getCurrentClip().y + target->getCurrentClip().h / 2 - pos.y));
				velocity_y = velocity * (target->getCurrentClip().y + target->getCurrentClip().h / 2 - pos.y) / sqrt((target->getCurrentClip().x + target->getCurrentClip().w / 2 - pos.x) *
					(target->getCurrentClip().x + target->getCurrentClip().w / 2 - pos.x) + (target->getCurrentClip().y + target->getCurrentClip().h / 2 - pos.y) * (target->getCurrentClip().y + target->getCurrentClip().h / 2 - pos.y));
				exactX += velocity_x;
				exactY += velocity_y;
				pos.x = (int)exactX;
				pos.y = (int)exactY;
			}
		}	
		else {
			if (SDL_GetTicks() - hitTime >=LiveTime) {
				complete = true;
			}
		}
	}
	else
		complete = true;
	
	
}
void fire_B::burn(Monster& m) {
	if ((m.getCurrentClip().x + m.getCurrentClip().w > pos.x) && (m.getCurrentClip().x < pos.x + pos.w) && (m.getCurrentClip().y + m.getCurrentClip().h >
		pos.y) && (m.getCurrentClip().y < pos.y + pos.h)) {
		m.attacked(damage);
	}
}
