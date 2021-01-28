#pragma once
#include "SDL.h"
#include <iostream>

std::ostream& operator<< (std::ostream& output, SDL_Rect Rect) {
	output << '{' << Rect.x << ", " << Rect.y
		<< ", " << Rect.w << ", " << Rect.y << "}\n";
	return output;
}