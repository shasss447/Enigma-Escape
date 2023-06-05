#include "Game.h"
Game::Game()
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
        cout << "init fail" << SDL_GetError() << endl;
    if (IMG_Init(IMG_INIT_PNG) == 0)
        cout << "image init fail" << IMG_GetError << endl;
    window = SDL_CreateWindow("car_race", 400, 100, 800, 554, 0);
    if (window == NULL)
        cout << "window fail" << SDL_GetError() << endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        cout << "renderer fail" << SDL_GetError() << endl;
    cellWidth = 32;
    cellHeight = 32;
    numRows = 17;
    numCols = 25;
    texturePaths = {
        "textures/stone.bmp",
        "textures/blackstone2.bmp",        
    };
    for (int i = 2; i < 17; i++)
    {
        A[i][2] = 1;
        A[2][i] = 1;
    }

}
void Game::loop()
{
    while (isRunning)
    {
        handleEvent();
        update();
        draw();
    }
    cleanup();
}
void Game::handleEvent()
{
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
                myplayer.y_pos -= myplayer.speed;
            if (event.key.keysym.sym == SDLK_DOWN)
                myplayer.y_pos += myplayer.speed;
            if (event.key.keysym.sym == SDLK_LEFT)
                myplayer.x_pos -= myplayer.speed;
            if (event.key.keysym.sym == SDLK_RIGHT)
                myplayer.x_pos += myplayer.speed;

        }
    }
}
void Game::update()
{
    myplayer.posrec.x = myplayer.x_pos;
    myplayer.posrec.y = myplayer.y_pos;
}
void Game::draw()
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderClear(renderer);
    Sprite mysprite1("player/car.bmp", renderer);
    myplayer.texture = mysprite1.gettex();
    for (const string& path : texturePaths)
    {
        Sprite mysprite(path, renderer);
        textures.push_back(mysprite.gettex());
    }
        

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
    SDL_RenderCopy(renderer, myplayer.texture, NULL, &myplayer.posrec);
    SDL_RenderPresent(renderer);
}
void Game::cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}