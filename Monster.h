#pragma once

#include<iostream>
#include"SDL.h"
#include "myTexture.h"
#include "Map.h"
#include "SDL_Image.h"
#include "Blood.h"
using namespace std;
class Monster {
protected:
	int health;
	int defense;
	int value;//殺掉的錢
	bool alive;
	int pos_x, pos_y;//動態陣列[i][j]
	int ex_pos_x, ex_pos_y;
	int speed;
	myTexture* texture;
	myTexture currentTexture;
	SDL_Rect* gSpriteClips;//SDL_Rect陣列[spite數]
	SDL_Rect currentClip;//正在顯示的那張sprite,//green Blood
	SDL_Rect redLineClip,greenLineClip;//Red Blood
	int WALKING_ANIMATION_FRAMES;//sprite有幾張
	int frame;//切sprite用
	int texturepos_x, texturepos_y;//在screen上的位子(左上角)(整數值)
	double exactX, exactY;//在screen上的位子(左上角)(實際值)
	int ex_texturepos_x, ex_texturepos_y;
	void move(Map& map);//陣列中move,裡面會call txeture_move,所以main call這個就好
	int win();
	int movecount;
	int framecount;//為了使sprite不會換太快
	bool start;//first call move
	Blood blood;
public:
	void texture_move(Map&);
	void attacked(const int& a);
	myTexture getCurrentTexture();
	SDL_Rect getCurrentClip();
	bool getAlive();
};
class hungyun : public Monster {
public:
	hungyun();
	hungyun(int level, Map& map);
};

class mingfeng :public Monster {
public:
	mingfeng();
	mingfeng(int level, Map& map);
};
class miku :public Monster {
public:
	miku();
	miku(int level, Map& map);
};
class bowgoal :public Monster {
public:
	bowgoal();
	bowgoal(int level, Map& map);
};
class sheep :public Monster {
public:
	sheep();
	sheep(int level, Map& map);
};
class trash :public Monster {
public:
	trash();
	trash(int level, Map& map);
};
