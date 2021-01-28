#include<iostream>
#include"SDL.h"
#include "myTexture.h"
#include "Map.h"
#include "SDL_Image.h"
#include "Monster.h"
#include "Blood.h"
#include "SDL_mixer.h"

using namespace std;
extern int money;
extern int HP;
extern SDL_Renderer* gRenderer;
Mix_Music* gWhatRUfucking;

bool Monster::getAlive() {
	return alive;
}
int Monster::win() {
	HP -= 1;
	alive = false;
	for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++) {
		texture[i].free();
	}
	Mix_PlayMusic(gWhatRUfucking, 1);
	return HP;
}
myTexture Monster::getCurrentTexture() {
	return currentTexture;
}
SDL_Rect Monster::getCurrentClip() {
	return currentClip;
}
hungyun::hungyun() {}
hungyun::hungyun(int level, Map& map) {
	if (level != 5) cout << "wrong monster type";
	start = false;
	health = 50000;
	alive = true;
	value = 350;
	speed = 1;
	pos_x = map.getEntry().getX();
	pos_y = map.getEntry().getY();
	ex_pos_x = pos_x;
	ex_pos_y = pos_y;
	frame = 0;
	framecount = 0;
	WALKING_ANIMATION_FRAMES = 2;
	gSpriteClips = new SDL_Rect[WALKING_ANIMATION_FRAMES];
	//�X�ͦa
	for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++) {
		gSpriteClips[i] = map.getScreenPos(pos_x, pos_y);
	}
	currentClip = gSpriteClips[0];
	texturepos_x = gSpriteClips[0].x;
	texturepos_y = gSpriteClips[0].y;
	exactX = texturepos_x;
	exactY = texturepos_y;
	ex_texturepos_x = texturepos_x;
	ex_texturepos_y = texturepos_y;
	movecount = 0;
	texture = new myTexture[WALKING_ANIMATION_FRAMES];
	texture[0].loadFromFile("img/hungyun_1.png");
	texture[1].loadFromFile("img/hungyun_2.png");
	currentTexture = texture[0];
	currentTexture.render(NULL, &currentClip, NULL, NULL, SDL_FLIP_NONE);
	blood = Blood(health);
	redLineClip.w = currentClip.w - 20;
	redLineClip.h = currentClip.h / 20;
	redLineClip.x = currentClip.x + 10;
	redLineClip.y = currentClip.y;
	greenLineClip.w = int(redLineClip.w * blood.getHPrate());
	greenLineClip.h = redLineClip.h;
	greenLineClip.y = redLineClip.y;
	greenLineClip.x = redLineClip.x;
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderDrawLine(gRenderer, redLineClip.x, redLineClip.y, redLineClip.x + redLineClip.w, redLineClip.y);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawLine(gRenderer, greenLineClip.x, greenLineClip.y, greenLineClip.x + greenLineClip.w, greenLineClip.y);
}


mingfeng::mingfeng() {}
mingfeng::mingfeng(int level, Map& map) {
	if (level != 4) cout << "wrong monster type";
	start = false;
	health = 1000;
	alive = true;
	value = 200;
	speed = 4;
	pos_x = map.getEntry().getX();
	pos_y = map.getEntry().getY();
	ex_pos_x = pos_x;
	ex_pos_y = pos_y;
	frame = 0;
	framecount = 0;
	WALKING_ANIMATION_FRAMES = 2;
	gSpriteClips = new SDL_Rect[WALKING_ANIMATION_FRAMES];
	for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++) {
		gSpriteClips[i] = map.getScreenPos(pos_x, pos_y);
	}
	currentClip = gSpriteClips[0];
	texturepos_x = gSpriteClips[0].x;
	texturepos_y = gSpriteClips[0].y;
	exactX = texturepos_x;
	exactY = texturepos_y;
	ex_texturepos_x = texturepos_x;
	ex_texturepos_y = texturepos_y;
	movecount = 0;
	texture = new myTexture[WALKING_ANIMATION_FRAMES];
	texture[0].loadFromFile("img/mingfeng_1.png");
	texture[1].loadFromFile("img/mingfeng_2.png");
	currentTexture = texture[0];
	currentTexture.render(NULL, &currentClip, NULL, NULL, SDL_FLIP_NONE);
	blood = Blood(health);
	redLineClip.w = currentClip.w - 20;
	redLineClip.h = currentClip.h / 20;
	redLineClip.x = currentClip.x + 10;
	redLineClip.y = currentClip.y;
	greenLineClip.w = int(redLineClip.w * blood.getHPrate());
	greenLineClip.h = redLineClip.h;
	greenLineClip.y = redLineClip.y;
	greenLineClip.x = redLineClip.x;
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderDrawLine(gRenderer, redLineClip.x, redLineClip.y, redLineClip.x + redLineClip.w, redLineClip.y);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawLine(gRenderer, greenLineClip.x, greenLineClip.y, greenLineClip.x + greenLineClip.w, greenLineClip.y);
}

miku::miku() {}
miku::miku(int level, Map& map) {
	if (level != 3) cout << "wrong monster type";
	start = false;
	health = 2500;
	alive = true;
	value = 150;
	speed = 2;
	pos_x = map.getEntry().getX();
	pos_y = map.getEntry().getY();
	ex_pos_x = pos_x;
	ex_pos_y = pos_y;
	frame = 0;
	framecount = 0;
	WALKING_ANIMATION_FRAMES = 6;
	gSpriteClips = new SDL_Rect[WALKING_ANIMATION_FRAMES];
	for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++) {
		gSpriteClips[i] = map.getScreenPos(pos_x, pos_y);
	}
	currentClip = gSpriteClips[0];
	texturepos_x = gSpriteClips[0].x;
	texturepos_y = gSpriteClips[0].y;
	exactX = texturepos_x;
	exactY = texturepos_y;
	ex_texturepos_x = texturepos_x;
	ex_texturepos_y = texturepos_y;
	movecount = 0;
	texture = new myTexture[WALKING_ANIMATION_FRAMES];
	texture[0].loadFromFile("img/miku_1.png");
	texture[1].loadFromFile("img/miku_2.png");
	texture[2].loadFromFile("img/miku_3.png");
	texture[3].loadFromFile("img/miku_4.png");
	texture[4].loadFromFile("img/miku_5.png");
	texture[5].loadFromFile("img/miku_6.png");
	currentTexture = texture[0];
	currentTexture.render(NULL, &currentClip, NULL, NULL, SDL_FLIP_NONE);
	blood = Blood(health);
	redLineClip.w = currentClip.w - 20;
	redLineClip.h = currentClip.h / 20;
	redLineClip.x = currentClip.x + 10;
	redLineClip.y = currentClip.y;
	greenLineClip.w = int(redLineClip.w * blood.getHPrate());
	greenLineClip.h = redLineClip.h;
	greenLineClip.y = redLineClip.y;
	greenLineClip.x = redLineClip.x;
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderDrawLine(gRenderer, redLineClip.x, redLineClip.y, redLineClip.x + redLineClip.w, redLineClip.y);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawLine(gRenderer, greenLineClip.x, greenLineClip.y, greenLineClip.x + greenLineClip.w, greenLineClip.y);
}
bowgoal::bowgoal() {}
bowgoal::bowgoal(int level, Map& map) {
	if (level != 2) cout << "wrong monster type";
	start = false;
	health = 3000;
	alive = true;
	value = 10;
	speed = 3;
	pos_x = map.getEntry().getX();
	pos_y = map.getEntry().getY();
	ex_pos_x = pos_x;
	ex_pos_y = pos_y;
	frame = 0;
	framecount = 0;
	WALKING_ANIMATION_FRAMES = 5;
	gSpriteClips = new SDL_Rect[WALKING_ANIMATION_FRAMES];
	for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++) {
		gSpriteClips[i] = map.getScreenPos(pos_x, pos_y);
	}
	currentClip = gSpriteClips[0];
	texturepos_x = gSpriteClips[0].x;
	texturepos_y = gSpriteClips[0].y;
	exactX = texturepos_x;
	exactY = texturepos_y;
	ex_texturepos_x = texturepos_x;
	ex_texturepos_y = texturepos_y;
	movecount = 0;
	texture = new myTexture[WALKING_ANIMATION_FRAMES];
	texture[0].loadFromFile("img/bowgoal_1.png");
	texture[1].loadFromFile("img/bowgoal_2.png");
	texture[2].loadFromFile("img/bowgoal_3.png");
	texture[3].loadFromFile("img/bowgoal_4.png");
	texture[4].loadFromFile("img/bowgoal_5.png");
	currentTexture = texture[0];
	currentTexture.render(NULL, &currentClip, NULL, NULL, SDL_FLIP_NONE);
	blood = Blood(health);
	redLineClip.w = currentClip.w - 20;
	redLineClip.h = currentClip.h / 20;
	redLineClip.x = currentClip.x + 10;
	redLineClip.y = currentClip.y;
	greenLineClip.w = int(redLineClip.w * blood.getHPrate());
	greenLineClip.h = redLineClip.h;
	greenLineClip.y = redLineClip.y;
	greenLineClip.x = redLineClip.x;
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderDrawLine(gRenderer, redLineClip.x, redLineClip.y, redLineClip.x + redLineClip.w, redLineClip.y);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawLine(gRenderer, greenLineClip.x, greenLineClip.y, greenLineClip.x + greenLineClip.w, greenLineClip.y);
}
sheep::sheep() {}
sheep::sheep(int level, Map& map) {
	if (level != 1) cout << "wrong monster type";
	start = false;
	health = 500;
	alive = true;
	value = 20;
	speed = 3;
	pos_x = map.getEntry().getX();
	pos_y = map.getEntry().getY();
	ex_pos_x = pos_x;
	ex_pos_y = pos_y;
	frame = 0;
	framecount = 0;
	WALKING_ANIMATION_FRAMES = 4;
	gSpriteClips = new SDL_Rect[WALKING_ANIMATION_FRAMES];
	for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++) {
		gSpriteClips[i] = map.getScreenPos(pos_x, pos_y);
	}
	currentClip = gSpriteClips[0];
	texturepos_x = gSpriteClips[0].x;
	texturepos_y = gSpriteClips[0].y;
	exactX = texturepos_x;
	exactY = texturepos_y;
	ex_texturepos_x = texturepos_x;
	ex_texturepos_y = texturepos_y;
	movecount = 0;
	texture = new myTexture[WALKING_ANIMATION_FRAMES];
	texture[0].loadFromFile("img/sheep_1.png");
	texture[1].loadFromFile("img/sheep_2.png");
	texture[2].loadFromFile("img/sheep_3.png");
	texture[3].loadFromFile("img/sheep_4.png");
	currentTexture = texture[0];
	currentTexture.render(NULL, &currentClip, NULL, NULL, SDL_FLIP_NONE);
	blood = Blood(health);
	redLineClip.w = currentClip.w - 20;
	redLineClip.h = currentClip.h / 20;
	redLineClip.x = currentClip.x + 10;
	redLineClip.y = currentClip.y;
	greenLineClip.w = int(redLineClip.w * blood.getHPrate());
	greenLineClip.h = redLineClip.h;
	greenLineClip.y = redLineClip.y;
	greenLineClip.x = redLineClip.x;
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderDrawLine(gRenderer, redLineClip.x, redLineClip.y, redLineClip.x + redLineClip.w, redLineClip.y);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawLine(gRenderer, greenLineClip.x, greenLineClip.y, greenLineClip.x + greenLineClip.w, greenLineClip.y);
}
trash::trash() {}
trash::trash(int level, Map& map) {
	if (level != 0) cout << "wrong monster type";
	start = false;
	health = 200;
	alive = true;
	value = 5;
	speed = 3;
	pos_x = map.getEntry().getX();
	pos_y = map.getEntry().getY();
	ex_pos_x = pos_x;
	ex_pos_y = pos_y;
	frame = 0;
	framecount = 0;
	WALKING_ANIMATION_FRAMES = 1;
	gSpriteClips = new SDL_Rect[WALKING_ANIMATION_FRAMES];
	for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++) {
		gSpriteClips[i] = map.getScreenPos(pos_x, pos_y);
	}
	currentClip = gSpriteClips[0];
	texturepos_x = gSpriteClips[0].x;
	texturepos_y = gSpriteClips[0].y;
	exactX = texturepos_x;
	exactY = texturepos_y;
	ex_texturepos_x = texturepos_x;
	ex_texturepos_y = texturepos_y;
	movecount = 0;
	texture = new myTexture[WALKING_ANIMATION_FRAMES];
	texture[0].loadFromFile("img/trash.png");
	currentTexture = texture[0];
	currentTexture.render(NULL, &currentClip, NULL, NULL, SDL_FLIP_NONE);
	blood = Blood(health);
	redLineClip.w = currentClip.w - 20;
	redLineClip.h = currentClip.h / 20;
	redLineClip.x = currentClip.x + 10;
	redLineClip.y = currentClip.y;
	greenLineClip.w = int(redLineClip.w * blood.getHPrate());
	greenLineClip.h = redLineClip.h;
	greenLineClip.y = redLineClip.y;
	greenLineClip.x = redLineClip.x;
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderDrawLine(gRenderer, redLineClip.x, redLineClip.y, redLineClip.x + redLineClip.w, redLineClip.y);
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawLine(gRenderer, greenLineClip.x, greenLineClip.y, greenLineClip.x + greenLineClip.w, greenLineClip.y);
}

void Monster::attacked(const int& a) {
	health -= a;
	if (health <= 0) {
		money += value;
		alive = false;
		for (int i = 0; i < WALKING_ANIMATION_FRAMES; i++)texture[i].free();
	}
	blood.attacked(health);
	return;
}
void Monster::move(Map& map_) {
	//upward
	int** map = map_.getMap();
	if (pos_y > 0 && pos_y - 1 != ex_pos_y && (map[pos_y - 1][pos_x] == 1 || map[pos_y - 1][pos_x] == 4)) {
		ex_pos_x = pos_x;
		ex_pos_y = pos_y;
		pos_y--;

	}

	//downward
	else if (pos_y < map_.getHeight() && pos_y + 1 != ex_pos_y && (map[pos_y + 1][pos_x] == 1 || map[pos_y + 1][pos_x] == 4)) {
		ex_pos_y = pos_y;
		ex_pos_x = pos_x;
		pos_y++;

	}

	//leftward
	else if (pos_x > 0 && pos_x - 1 != ex_pos_x && (map[pos_y][pos_x - 1] == 1 || map[pos_y][pos_x - 1] == 4)) {
		ex_pos_x = pos_x;
		ex_pos_y = pos_y;
		pos_x--;

	}

	//rightward
	else if (pos_x < map_.getWidth() && pos_x + 1 != ex_pos_x && (map[pos_y][pos_x + 1] == 1 || map[pos_y][pos_x + 1] == 4)) {
		ex_pos_x = pos_x;
		ex_pos_y = pos_y;
		pos_x++;

	}
	else {
		cout << "Error: stuck" << endl;
		return;
	}
	SDL_Rect explace = map_.getScreenPos(ex_pos_x, ex_pos_y);
	ex_texturepos_x = explace.x;
	ex_texturepos_y = explace.y;
	if (pos_x == map_.getHome().getX() && pos_y == map_.getHome().getY()) {
		this->win();
		return;
	}
	else {
		this->texture_move(map_);//��class map�ǵ�texture_move
		return;
	}
}

void Monster::texture_move(Map& map) {
	if (alive) {
		currentTexture = texture[frame];

		//update currentClip
		SDL_Rect newplace = map.getScreenPos(pos_x, pos_y);
		//�����@��callMove
		if (((texturepos_x > (newplace.x + 1) && ex_texturepos_x < newplace.x)) || (texturepos_y > newplace.y + 1 && ex_texturepos_y < newplace.y) || (texturepos_y < newplace.y - 1 && ex_texturepos_y > newplace.y) || (texturepos_x < newplace.x - 1 && ex_texturepos_x > newplace.x)) {
			movecount = 0;
			this->move(map);
		}
		if (!start && (texturepos_x == map.getScreenPos(map.getEntry().getX(), map.getEntry().getY()).x && texturepos_y == map.getScreenPos(map.getEntry().getX(), map.getEntry().getY()).y)) {
			start = true;
			movecount = 0;
			this->move(map);
		}
		//update texturepos
		//��������
		exactX += (double(newplace.x) - double(ex_texturepos_x)) / 1000 * speed;
		exactY += (double(newplace.y) - double(ex_texturepos_y)) / 1000 * speed;
		movecount += 0.001 * speed;
		texturepos_x = (int)exactX;
		texturepos_y = (int)exactY;
		currentClip.x = texturepos_x;
		currentClip.y = texturepos_y;
		currentTexture.render(NULL, &currentClip, NULL, NULL, SDL_FLIP_NONE);
		redLineClip.w = currentClip.w - 20;
		redLineClip.h = currentClip.h / 20;
		redLineClip.x = currentClip.x + 10;
		redLineClip.y = currentClip.y;
		greenLineClip.w = int(redLineClip.w * blood.getHPrate());
		greenLineClip.h = redLineClip.h;
		greenLineClip.y = redLineClip.y;
		greenLineClip.x = redLineClip.x;
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawLine(gRenderer, redLineClip.x, redLineClip.y, redLineClip.x + redLineClip.w, redLineClip.y);
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawLine(gRenderer, greenLineClip.x, greenLineClip.y, greenLineClip.x + greenLineClip.w, greenLineClip.y);
		//Cycle animation
		++framecount;
		if (framecount >= 100 / pow(WALKING_ANIMATION_FRAMES, 0.5)) {
			++frame;
			framecount = 0;
		}
		if (frame >= WALKING_ANIMATION_FRAMES) frame = 0;


	}
	return;
}
