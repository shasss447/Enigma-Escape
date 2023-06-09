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
	enum FacingDirection { Up, Down, Left, Right };
	FacingDirection previousDirection;
	FacingDirection  currentDirection;
	int angle;
	bool change;

};

