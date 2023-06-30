#include "Player.h"

Player::Player()
{
	 p_pos.first= 120;
	p_pos.second = 100;
	speed = 20;
	posrec = {
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
