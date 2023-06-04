#pragma once
#include<SDL.h>
class player
{
public:
	player();
	float x_pos;
	float y_pos;
	int speed;
	SDL_Rect posrec;
};

