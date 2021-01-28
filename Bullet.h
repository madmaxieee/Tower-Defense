#ifndef BULLET
#define BULLET

#include"Monster.h"
class bullet {
protected:
	double velocity;
	//velocity
	//current position
	//target position
	Monster* target;
	double velocity_x, velocity_y;
	SDL_Rect pos;
	double exactX, exactY;
	bool complete;
public:
	bullet();
	bullet(SDL_Rect& ,Monster&);
	~bullet();
	int damage;
	virtual void render() = 0;
	void move();
	int getx() const;
	int gety() const;
	bool getComplete() ;
};
class average_B :public bullet {
	myTexture* avgB_Texture;
public:
	average_B();
	average_B(SDL_Rect&, Monster&);
	void render();
};
class snip_B :public bullet {
	myTexture* snipB_Texture;
public:
	snip_B();
	snip_B(SDL_Rect&, Monster&);
	void render();
};
class fire_B :public bullet {
	Uint32 hitTime;
	int LiveTime;
	bool hit;
	myTexture* fireB_Texture;
public:
	void move();
	void burn(Monster&);
	fire_B();
	fire_B(SDL_Rect&, Monster&);
	void render();
};
#endif