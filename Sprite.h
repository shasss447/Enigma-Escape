#pragma once
#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<string>

using namespace std;

class Sprite
{
public:
	Sprite(string filepath,SDL_Renderer*renderer);
	SDL_Texture* gettex();

private:
	SDL_Texture* tex;
};

