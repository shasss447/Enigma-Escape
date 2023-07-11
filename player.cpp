#include "Player.h"

//FILE TO SET PLAYER'S INITIAL STATES
Player::Player()
{
	p_pos.first= 25;
	p_pos.second = 25;

	speed = 20;

	posrec = 
	{
	 p_pos.first,
	 p_pos.second,
	 30,
	 30
	};

	texture = NULL;

	previousDirection = FacingDirection::Left;
	currentDirection = FacingDirection::Left;
	angle = 0;
	change = false;
}
