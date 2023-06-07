#include "Game.h"
Game::Game()
{
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
        cout << "init fail" << SDL_GetError() << endl;
    if (IMG_Init(IMG_INIT_PNG) == 0)
        cout << "image init fail" << IMG_GetError << endl;
    window = SDL_CreateWindow("car_race", 400, 100, 800, 600, 0);
    if (window == NULL)
        cout << "window fail" << SDL_GetError() << endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        cout << "renderer fail" << SDL_GetError() << endl;
    cellWidth = 25;
    cellHeight = 25;
    numRows = 24;
    numCols = 32;
    grid.resize(numRows,vector<int>(numCols,0));
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            if (i>=8&&i<14||i>=16&&i<19)
                grid[i][j] = INT_MAX;
        }
    }
    texturePaths = {
        "textures/stone.bmp",
        "textures/blackstone2.bmp",        
    };
    
    keys = SDL_GetKeyboardState(NULL);
    offSetx = 0;
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
            {
                if(myplayer.y_pos>25)
                {
                    myplayer.y_pos -= myplayer.speed;
                    offSety -= myplayer.speed;
                }
            }
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                if(myplayer.y_pos<600)
                {
                    myplayer.y_pos += myplayer.speed;
                    offSety += myplayer.speed;
                }
            }
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                if(myplayer.x_pos>25)
                {
                    myplayer.x_pos -= myplayer.speed;
                    offSetx -= myplayer.speed; // Adjust the X offset when moving left
                }
            }
            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                if(myplayer.x_pos<800)
                {
                    myplayer.x_pos += myplayer.speed;
                    offSetx += myplayer.speed; // Adjust the X offset when moving right
                }
            }

        }
    }
}
void Game::update()
{
    myplayer.posrec.x = myplayer.x_pos -offSetx;
    myplayer.posrec.y = myplayer.y_pos -offSety;
}
void Game::draw()
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
    SDL_RenderClear(renderer);
    Sprite mysprite1("player/car.bmp", renderer);
    Sprite mysprite2("player/policecar.bmp",renderer);
    myplayer.texture = mysprite1.gettex();
    enemy.texture = mysprite2.gettex();
    for (const string& path : texturePaths)
    {
        Sprite mysprite(path, renderer);
        textures.push_back(mysprite.gettex());
    }
        

    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            int x = (col * cellWidth) - offSetx;
            int y = (row * cellHeight) - offSety;

            SDL_Texture* currentTexture = nullptr;
            int cellType = grid[row][col];  // Assume grid stores cell types (e.g., 0 for road, 1 for grass, 2 for rock)
           if(cellType==0) 
              currentTexture = textures[0];
           else
              currentTexture = textures[1];
                // Handle other cell types as needed
            // Draw vertical line
            //SDL_RenderDrawLine(renderer, x, 0, x, 600);

            // Draw horizontal line
            //SDL_RenderDrawLine(renderer, 0, y, 800, y);
            SDL_Rect cellRect = { x, y, cellWidth, cellHeight };
            SDL_RenderCopy(renderer, currentTexture, nullptr, &cellRect);
        }
    }
    SDL_RenderCopy(renderer, myplayer.texture, NULL, &myplayer.posrec);
    SDL_RenderCopy(renderer, enemy.texture, NULL, &enemy.posrec);
    SDL_RenderPresent(renderer);
}
void Game::cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}