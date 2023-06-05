#pragma once
#include<SDL.h>
class Player
{
public:
	Player();
	float x_pos;
	float y_pos;
	int speed;
	SDL_Rect posrec;
	SDL_Texture* texture;
};

