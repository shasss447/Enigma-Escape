#pragma once
#include<SDL.h>
class Enemy
{
public:
	Enemy();
	float x_pos;
	float y_pos;
	int speed;
	SDL_Rect posrec;
	SDL_Texture* texture;
};

