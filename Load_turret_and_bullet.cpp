#include "SDL.h"
#include "SDL_image.h"
#include "mytexture.h"
#include<iostream>
#include "SDL_mixer.h"
myTexture avgTexture[3];
myTexture snipTexture[3];
myTexture fireT_Texture[3];
myTexture bullet_textures[5];
myTexture fireTextures[12];
Mix_Chunk* gHit;
Mix_Chunk* gburn;
extern Mix_Music* coverBGM;
extern Mix_Music* gameBGM;
extern Mix_Music* gWhatRUfucking;
extern SDL_Renderer* gRenderer;
extern SDL_Window* gWindow;


void Load_Turret() {
	if (!avgTexture[0].loadFromFile("./img/turrets/5-1.png"))
		std::cout << "failed to load 5-1";
	if (!avgTexture[1].loadFromFile("./img/turrets/5-2.png"))
		std::cout << "failed to load 5-2";
	if (!avgTexture[2].loadFromFile("img/turrets/5-3.png"))
		std::cout << "failed to load 5-3";
	if(!snipTexture[0].loadFromFile("img/turrets/2-1.png"))
		std::cout << "failed to load 2-1";
	if (!snipTexture[1].loadFromFile("img/turrets/2-2.png"))
		std::cout << "failed to load 2-2";
	if (!snipTexture[2].loadFromFile("img/turrets/4-2.png"))
		std::cout << "failed to load 4-2";
	if (!fireT_Texture[0].loadFromFile("img/turrets/3-1.png"))
		std::cout << "failed to load 3-1";
	if (!fireT_Texture[1].loadFromFile("img/turrets/3-2.png"))
		std::cout << "failed to load 3-2";
	if (!fireT_Texture[2].loadFromFile("img/turrets/3-3.png"))
		std::cout << "failed to load 3-3";

	//std::cout << "success";
}
void Load_Bullet() {
	if (!bullet_textures[0].loadFromFile("./img/dot.png"))
		std::cout << "failed to load bullet texture0";
	if (!bullet_textures[1].loadFromFile("./img/bullet.png"))
		std::cout << "failed to load bullet texture1";
	if (!bullet_textures[2].loadFromFile("./img/dot.png"))
		std::cout << "failed to load bullet2";
	if (!fireTextures[0].loadFromFile("./img/fire1.png"))
		std::cout << "failed to load fire1";
	if (!fireTextures[1].loadFromFile("./img/fire2.png"))
		std::cout << "failed to load fire2";
	if (!fireTextures[2].loadFromFile("./img/fire3.png"))
		std::cout << "failed to load fire3";
	if (!fireTextures[3].loadFromFile("./img/fire4.png"))
		std::cout << "failed to load fire4";
	if (!fireTextures[4].loadFromFile("./img/fire5.png"))
		std::cout << "failed to load fire5";
	if (!fireTextures[5].loadFromFile("./img/fire6.png"))
		std::cout << "failed to load fire6";
	if (!fireTextures[6].loadFromFile("./img/fire7.png"))
		std::cout << "failed to load fire7";
	if (!fireTextures[7].loadFromFile("./img/fire8.png"))
		std::cout << "failed to load fire8";
	if (!fireTextures[8].loadFromFile("./img/fire9.png"))
		std::cout << "failed to load fire9";
	if (!fireTextures[9].loadFromFile("./img/fire10.png"))
		std::cout << "failed to load fire10";
	if (!fireTextures[10].loadFromFile("./img/fire11.png"))
		std::cout << "failed to load fire11";
	if (!fireTextures[11].loadFromFile("./img/fire12.png"))
		std::cout << "failed to load fire12";
	for (int i = 0; i < 12; i++) {
		fireTextures[i].setBlendMode(SDL_BLENDMODE_BLEND);
		fireTextures[i].setAlpha(0xc0);
	}

}

void loadSFX() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	else {
		//std::cout << "SUCCESS";
	}
	gburn = Mix_LoadWAV("./sound_effect/burn.wav");
	if (gburn == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	gHit = Mix_LoadWAV("./sound_effect/hit.wav");
	if (gHit == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	gWhatRUfucking = Mix_LoadMUS("sound_effect/WhatAreYouFucking.mp3");
	coverBGM = Mix_LoadMUS("sound_effect/coverBGM.mp3");
	gameBGM = Mix_LoadMUS("sound_effect/gameBGM.mp3");
}

//void close_turret() {
//	//Free loaded images
//	avgTexture[0].free();
//	avgTexture[1].free();
//	avgTexture[2].free();
//	snipTexture[0].free();
//
//	//Destroy window
//	SDL_DestroyRenderer(gRenderer);
//	SDL_DestroyWindow(gWindow);
//	gWindow = NULL;
//	gRenderer = NULL;
//
//	//Quit SDL subsystems
//	IMG_Quit();
//	SDL_Quit();
//}



