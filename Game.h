#pragma once
#include"Player.h"
#include<vector>
#include"Sprite.h"
#include"Enemy.h"
#include <queue>
class Game
{
public:
	Game();
	void loop();
	void handleEvent();
	void update();
	void draw();
	void cleanup();
	void shortestpath(int p_x, int p_y, int d_x, int d_y);
	pair<int, int>de_pos;

private:

	SDL_Renderer* renderer;
	SDL_Window* window;
	bool isRunning = true;
    Player myplayer;
	Enemy enemy;
	int cellWidth;
	int cellHeight;
	int numRows;
	int numCols;
	vector<vector<int>>grid;
	vector<string> texturePaths;
	vector<SDL_Texture*> textures;
	const Uint8* keys;
	pair<int, int>offset;
};

