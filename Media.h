#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
// \param path: path to the media file
// \param stretch Rect
SDL_Texture* loadTexture(std::string path);