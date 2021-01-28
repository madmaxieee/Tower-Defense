#include "SDL.h"
#include "Map.h"
#include "Media.h"
#include "myTexture.h"
#include "myButton.h"
#include "myTimer.h"
#include "pause_menu.h"
#include "Monster.h"
#include "gameState.h"
#include "Monster.h"
#include "turret.h"
#include <Windows.h>
#include "time.h"
#include "Cover.h"
#include "SDL_Mixer.h"

int money = 0;
int HP = 20;

extern myTexture snipTexture[4];
extern myTexture fireT_Texture[4];
extern myTexture avgTexture[4];
extern myTexture bullet_textures[5];
//extern void close_turret();
void extern Load_Turret();
void extern Load_Bullet();
void extern loadSFX();
std::vector<turret*> turrets;

trash* trashes[100];
sheep* sheeps[100];
bowgoal* bowgoals[100];
miku* mikus[100];
mingfeng* mingfengs[100];
hungyun* hungyuns[100];

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;
Mix_Music* coverBGM;
Mix_Music* gameBGM;

gameState STATE = MAIN_MENU;

//main timer
myTimer timer;

int main(int argc, char* argv[]) {
	//hide concole
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	srand(time(NULL));

	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//load Media
		myTexture myDirtTexture, myCobbleTexture, myLeavesTexture, myTurretBaseTexture, myBGTexture;
		myDirtTexture.loadFromFile("img/dirt.png");
		myCobbleTexture.loadFromFile("img/cobble.png");
		myLeavesTexture.loadFromFile("img/leaves.png");
		myTurretBaseTexture.loadFromFile("img/turretbase.png");
		myBGTexture.loadFromFile("img/bg_wood.png");
		Load_Turret();
		Load_Bullet();
		loadSFX();

		//set elements
		Map _map(0);
		PauseButton pause_button;
		PauseMenu pause_menu = PauseMenu();
		ContinueButton continue_button;
		TurretMenu turret_menu;
		Cover cover;

		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(gRenderer);

		//for frame control
		uint32_t start_t = SDL_GetTicks();
		uint64_t frame_count = 0;

		//Event handler
		SDL_Event event;

		Pos build_target;
		int random;
		int monster_count[6]{ 0, 0, 0, 0, 0, 0 };

		Mix_PlayMusic(coverBGM, -1);
		//main loop
		do {
			switch (STATE) {
			case MAIN_MENU:
				cover.render();
				if(cover.handleEvent(&event))
					timer.start();
				break;
			case PLAY:
				random = rand() % ( (50 - ((timer.getTicks() / 1000) % 50)) * 400);

				for (int i = 0; i < 6; i++) {
					if (monster_count[i] >= 100) monster_count[i] -= 100;;
				}
				if (random < 15) {
					trash* temp = new trash(0, _map);
					trashes[monster_count[0]] = temp;
					monster_count[0]++;
				}
				else if (random < 25) {
					sheep* temp = new sheep(1, _map);
					sheeps[monster_count[1]] = temp;
					monster_count[1]++;
				}
				else if (random < 35) {
					bowgoal* temp = new bowgoal(2, _map);
					bowgoals[monster_count[2]] = temp;
					monster_count[2]++;
				}
				else if (random < 43) {
					miku* temp = new miku(3, _map);
					mikus[monster_count[3]] = temp;
					monster_count[3]++;
				}
				else if (random < 48) {
					mingfeng* temp = new mingfeng(4, _map);
					mingfengs[monster_count[4]] = temp;
					monster_count[4]++;
				}
				else if (random < 50) {
					hungyun* temp = new hungyun(5, _map);
					hungyuns[monster_count[5]] = temp;
					monster_count[5]++;
				}

				SDL_RenderClear(gRenderer);
				timer.unpause();
				myBGTexture.render();
				build_target = _map.handleEvent(&event, build_target);
				_map.render(myLeavesTexture, myDirtTexture, myCobbleTexture);
				pause_button.render();
				pause_button.handleEvent(&event);
				for (int i = 0; i < turrets.size(); i++) {
					turrets.at(i)->render();
					for (int j = 0; j < monster_count[0]; j++) {
						trashes[j]->texture_move(_map);
						turrets[i]->sensor(*trashes[j]);
					}
					for (int j = 0; j < monster_count[1]; j++) {
						sheeps[j]->texture_move(_map);
						turrets[i]->sensor(*sheeps[j]);
					}
					for (int j = 0; j < monster_count[2]; j++) {
						bowgoals[j]->texture_move(_map);
						turrets[i]->sensor(*bowgoals[j]);
					}
					for (int j = 0; j < monster_count[3]; j++) {
						mikus[j]->texture_move(_map);
						turrets[i]->sensor(*mikus[j]);
					}
					for (int j = 0; j < monster_count[4]; j++) {
						mingfengs[j]->texture_move(_map);
						turrets[i]->sensor(*mingfengs[j]);
					}
					for (int j = 0; j < monster_count[5]; j++) {
						hungyuns[j]->texture_move(_map);
						turrets[i]->sensor(*hungyuns[j]);
					}
				}
				timer.render();
				
				break;
			case PAUSE:
				timer.pause();
				pause_menu.render();
				pause_menu.handleEvent(&event);
				break;
			case BUILD_TURRET:
				timer.pause();
				turret_menu.pos = build_target;
				turret_menu.render();
				turret_menu.handleEvent(&event);
				break;
			}

			while ((SDL_GetTicks() - start_t < frame_count * 1000 / 60) || SDL_PollEvent(&event)) {
				//control frame rate
			}

			//Update screen
			SDL_RenderPresent(gRenderer);
			frame_count++;
		} while (event.type != SDL_QUIT);
	}

	//Free resources and close SDL
	close();

	return 0;
}