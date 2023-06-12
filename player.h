#pragma once
#include<iostream>
#include<SDL.h>
#include<utility>
using namespace std;
class Player
{
public:
	Player();
	std::pair<int, int>p_pos;
	int speed;
	SDL_Rect posrec;
	SDL_Texture* texture;
	enum FacingDirection { Up, Down, Left, Right };
	FacingDirection previousDirection;
	FacingDirection  currentDirection;
	int angle;
	bool change;

};

