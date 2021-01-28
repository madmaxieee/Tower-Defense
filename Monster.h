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
	int value;//��������
	bool alive;
	int pos_x, pos_y;//�ʺA�}�C[i][j]
	int ex_pos_x, ex_pos_y;
	int speed;
	myTexture* texture;
	myTexture currentTexture;
	SDL_Rect* gSpriteClips;//SDL_Rect�}�C[spite��]
	SDL_Rect currentClip;//���b��ܪ����isprite,//green Blood
	SDL_Rect redLineClip,greenLineClip;//Red Blood
	int WALKING_ANIMATION_FRAMES;//sprite���X�i
	int frame;//��sprite��
	int texturepos_x, texturepos_y;//�bscreen�W����l(���W��)(��ƭ�)
	double exactX, exactY;//�bscreen�W����l(���W��)(��ڭ�)
	int ex_texturepos_x, ex_texturepos_y;
	void move(Map& map);//�}�C��move,�̭��|call txeture_move,�ҥHmain call�o�ӴN�n
	int win();
	int movecount;
	int framecount;//���F��sprite���|���ӧ�
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
