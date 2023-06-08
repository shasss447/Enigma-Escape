#include "Player.h"

Player::Player()
{
	x_pos = 375.f;
	y_pos = 275.f;
	speed = 5;
	posrec = {
	 (int)x_pos,
	 (int)y_pos,
	 50,
	 50
	};
	texture = NULL;
}
