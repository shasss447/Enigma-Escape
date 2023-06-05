#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<vector>
#include"Player.h"
#include"Game.h"
using namespace std;


int main(int argc, char* argv[])
{  
    Game game;
    game.loop();
	return 0;
}