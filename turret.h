#ifndef TURRET_H
#define TURRET_H
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "mytexture.h"
#include "Bullet.h"
#include "Monster.h"

using namespace std;
enum Amode { Fly, Ground, Both };

class turret {
protected:
	Monster* target;
	Uint32 lastTime;
	double attack_range;
	int attack_speed;
	Amode attackmode;
	SDL_Rect place;
	bool Lockedup;
	int bulletCount;
	int level;
	double direction;
	Uint32 builtTime;
	
public:
	
	turret();
	~turret();
	turret(int x, int y);
	void rotate();
	//get state of lock
	bool getL() const;
	virtual void Upgrade()=0;
	virtual bool attack(Monster& m) = 0;
	bool sensor(Monster& m);
	virtual void render() = 0;

};
class average_T : public turret {
private:
	average_B* AllBullet[10];
public:
	void render();
	~average_T();
	average_T();
	void Upgrade();
	average_T(int x, int y);
	bool attack(Monster& m);
};
class sniper : public turret {
private:
	snip_B* AllBullet[10];
public:
	void render();
	~sniper();
	void Upgrade();
	sniper();
	sniper(int x, int y);
	bool attack(Monster& m);
};
class fire :public turret {
private:
	fire_B* AllBullet[20];
public:
	void render();
	void sensor(Monster& m);
	turret::sensor;
	~fire();
	fire();
	void Upgrade();
	fire(int x, int y);
	bool attack(Monster& m);
};
#endif