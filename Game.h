#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include"Player.h"
#include<vector>
#include"Sprite.h"
using namespace std;
class Game
{
public:
	Game();
	void loop();
	void handleEvent();
	void update();
	void draw();
	void cleanup();

private:

	SDL_Renderer* renderer;
	SDL_Window* window;
	bool isRunning = true;
    Player myplayer;
	int cellWidth;
	int cellHeight;
	int numRows;
	int numCols;
	int A[17][25];
	vector<string> texturePaths;
	vector<SDL_Texture*> textures;
};

