#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<vector>
#include"player.h"
using namespace std;
SDL_Renderer* renderer;
SDL_Window* window;
bool isRunning = 1;
SDL_Texture* loadIm(string path)
{
    SDL_Surface* temsur = IMG_Load(path.c_str());
    if (temsur == NULL)
        cout << "surface fail" << SDL_GetError() << endl;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, temsur);
    if (tex == NULL)
        cout << "surface fail" << SDL_GetError() << endl;
    SDL_FreeSurface(temsur);
    return tex;
}
int main(int argc, char* argv[])
{  
    int cellWidth = 32;
    int cellHeight = 32;
    int numRows = 17;
    int numCols = 25;
    int A[17][25] = { 0 };
    for (int i = 2; i < 17; i++)
    {
        A[i][2] = 1;
        A[2][i] = 1;
    }
    vector<std::string> texturePaths = {
    "textures/stone.bmp",
    "textures/blackstone2.bmp",
    // Add more texture paths as needed
    };
    vector<SDL_Texture*> textures;
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
        cout << "init fail" << SDL_GetError() << endl;
    if (IMG_Init(IMG_INIT_PNG) == 0)
        cout << "image init fail" << IMG_GetError << endl;
    window = SDL_CreateWindow("car_race", 400, 100, 800, 554, 0);
    if(window==NULL)
        cout << "window fail" << SDL_GetError() << endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        cout << "renderer fail" << SDL_GetError() << endl;
    
    player player;
    player.texture= loadIm("player/car.bmp");
    while (isRunning)
    {
        Uint64 start = SDL_GetPerformanceCounter();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
                break;
            }
                

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_UP)
                    player.y_pos -= player.speed;
                if (event.key.keysym.sym == SDLK_DOWN)
                    player.y_pos += player.speed;
                if (event.key.keysym.sym == SDLK_LEFT)
                    player.x_pos -= player.speed;
                if (event.key.keysym.sym == SDLK_RIGHT)
                    player.x_pos += player.speed;

            }
        }

        player.posrec.x = player.x_pos;
        player.posrec.y = player.y_pos;
        SDL_SetRenderDrawColor(renderer,255,0,255, 255);
        SDL_RenderClear(renderer);
        for (const string& path : texturePaths)
            textures.push_back(loadIm(path));
       

        for (int row = 0; row < numRows; ++row)
        {
            for (int col = 0; col < numCols; ++col)
            {
                int x = col * cellWidth;
                int y = row * cellHeight;

                SDL_Texture* currentTexture = nullptr;
                int cellType = A[row][col];  // Assume grid stores cell types (e.g., 0 for road, 1 for grass, 2 for rock)
                switch (cellType) {
                case 0:
                    currentTexture = textures[0];
                    break;
                case 1:
                    currentTexture = textures[1];
                    break;               
                    // Handle other cell types as needed
                }
                // Draw vertical line
                //SDL_RenderDrawLine(renderer, x, 0, x, 600);

                // Draw horizontal line
                //SDL_RenderDrawLine(renderer, 0, y, 800, y);
                SDL_Rect cellRect = { x, y, cellWidth, cellHeight };
                SDL_RenderCopy(renderer, currentTexture, nullptr, &cellRect);
            }
        }
        SDL_RenderCopy(renderer,player.texture,NULL, &player.posrec);
        SDL_RenderPresent(renderer);
        Uint64 end = SDL_GetPerformanceCounter();
        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
        SDL_Delay(floor(16.666f - elapsedMS));
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;
}