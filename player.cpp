#include "Player.h"

Player::Player()
{
	 p_pos.first= 375;
	p_pos.second = 275;
	speed = 25;
	posrec = {
	p_pos.first,
	p_pos.second,
	 50,
	 50
	};
	texture = NULL;
	previousDirection = FacingDirection::Left;
	currentDirection = FacingDirection::Left;
	angle = 0;
	change = false;

}
