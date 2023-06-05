#include "player.h"

player::player()
{
	x_pos = 100.f;
	y_pos = 100.f;
	speed = 5;
	posrec = {
	 (int)x_pos,
	 (int)y_pos,
	 32,
	 32
	};
	texture = NULL;
}
