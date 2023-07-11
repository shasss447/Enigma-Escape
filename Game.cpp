#include "Game.h"
#include"Helper.h"
#include"map.h"

//STARTING OF THE GAME
Game::Game()
{
    //CREATING WINDOW AND LOADING IMAGES
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
        cout << "init fail" << SDL_GetError() << endl;
    if (IMG_Init(IMG_INIT_PNG) == 0)
        cout << "image init fail" << IMG_GetError << endl;
    window = SDL_CreateWindow("car_race",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1000, 600,0);
    if (window == NULL)
        cout << "window fail" << SDL_GetError() << endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
        cout << "renderer fail" << SDL_GetError() << endl;
    cellWidth = 20;
    cellHeight = 20;
    numRows = 30;
    numCols = 50;
    createmap(grid, numRows, numCols);  //CREATING THE MAZE
    texturePaths = {                   //ADDING TEXTURES TO THE MAP
        "textures/stone.bmp",
        "textures/blackstone2.bmp"
    };
    
    keys = SDL_GetKeyboardState(NULL);
}

//LOOP FUNCTION TO KEEP THE GAME RUNNING
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

//FUNCTION TO HANDLE ALL THE KEY PRESS EVENTS
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

            //HANDLING MOVEMENTS
            if (event.key.keysym.sym == SDLK_UP)
            {
                if (grid[(myplayer.p_pos.second - cellWidth)/25][myplayer.p_pos.first / 25] == 1)
                {
                    myplayer.p_pos.second -= myplayer.speed;
                    myplayer.previousDirection = myplayer.currentDirection;
                    myplayer.currentDirection = Player::FacingDirection::Up;
                    myplayer.change = true;
                }
            }

            if (event.key.keysym.sym == SDLK_DOWN)
            {
                if (grid[((myplayer.p_pos.second + cellWidth) / 25)+1][myplayer.p_pos.first / 25] == 1)
                {
                    myplayer.p_pos.second += myplayer.speed;
                    myplayer.previousDirection = myplayer.currentDirection;
                    myplayer.currentDirection = Player::FacingDirection::Down;
                    myplayer.change = true;
                }
            }

            if (event.key.keysym.sym == SDLK_LEFT)
            {
                if (grid[myplayer.p_pos.second / 25][(myplayer.p_pos.first - cellHeight)/25] == 1)
                {
                    myplayer.p_pos.first -= myplayer.speed;
                    myplayer.previousDirection = myplayer.currentDirection;
                    myplayer.currentDirection = Player::FacingDirection::Left;
                    myplayer.change = true;
                }
            }

            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                if (grid[myplayer.p_pos.second / 25][((myplayer.p_pos.first + cellHeight) / 25)+1] == 1)
                {
                    myplayer.p_pos.first += myplayer.speed;
                    myplayer.previousDirection = myplayer.currentDirection;
                    myplayer.currentDirection = Player::FacingDirection::Right;
                    myplayer.change = true;
                }
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_M)
            {
                shortestpath(numRows,numCols, myplayer.p_pos.second, myplayer.p_pos.first, path,grid);
            }

        }

        //HANDLING MOUSE CLICK
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT) 
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                int blockX = mouseX / cellWidth;
                int blockY = mouseY / cellHeight;
                cout<<blockX*25<<" "<<blockY*25<<endl;
            }
        }
    }
}

//FUNCTION TO UPDATE THE POSITION AND FACE DIRECTION
void Game::update()
{

    myplayer.posrec.x = myplayer.p_pos.first;
    myplayer.posrec.y = myplayer.p_pos.second;

    if (myplayer.change)
    {

        if (myplayer.previousDirection == Player::FacingDirection::Right)
        {
            if (myplayer.currentDirection == Player::FacingDirection::Up)
                myplayer.angle = myplayer.angle - 90;
            else if (myplayer.currentDirection == Player::FacingDirection::Down)
                myplayer.angle = myplayer.angle + 90;
            else if (myplayer.currentDirection == Player::FacingDirection::Left)
                //flip = SDL_FLIP_HORIZONTAL;
                myplayer.angle = myplayer.angle + 180;

        }

        else if (myplayer.previousDirection == Player::FacingDirection::Up)
        {
            if (myplayer.currentDirection == Player::FacingDirection::Left)
                myplayer.angle = myplayer.angle - 90;
            else if (myplayer.currentDirection == Player::FacingDirection::Right)
                myplayer.angle = myplayer.angle + 90;
            else if (myplayer.currentDirection == Player::FacingDirection::Down)
                //flip = SDL_FLIP_VERTICAL;
                myplayer.angle = myplayer.angle + 180;
        }

        else if (myplayer.previousDirection == Player::FacingDirection::Left)
        {
            if (myplayer.currentDirection == Player::FacingDirection::Down)
                myplayer.angle = myplayer.angle - 90;
            else if (myplayer.currentDirection == Player::FacingDirection::Up)
                myplayer.angle = myplayer.angle + 90;
            else if (myplayer.currentDirection == Player::FacingDirection::Right)
                //flip = SDL_FLIP_HORIZONTAL;
                myplayer.angle = myplayer.angle + 180;
        }

        else if (myplayer.previousDirection == Player::FacingDirection::Down)
        {
            if (myplayer.currentDirection == Player::FacingDirection::Right)
                myplayer.angle = myplayer.angle + 90;
            else if (myplayer.currentDirection == Player::FacingDirection::Left)
                myplayer.angle = myplayer.angle - 90;
            else if (myplayer.currentDirection == Player::FacingDirection::Up)
                //flip = SDL_FLIP_VERTICAL;
                myplayer.angle = myplayer.angle + 180;
        }

        myplayer.change = false;
    }
}

//FUNCTION TO DRAW TEXTURES AND SPRITE ON SCREEN
void Game::draw()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    Sprite mysprite1("player/car.bmp", renderer);
    myplayer.texture = mysprite1.gettex();
    for (const string& path : texturePaths)
    {
        Sprite mysprite(path, renderer);
        textures.push_back(mysprite.gettex());
    }
        
    //SETTING TEXTURE TO THE MAZE
    for (int row = 0; row < numRows; ++row)
    {
        for (int col = 0; col < numCols; ++col)
        {
            int x = (col * cellWidth);
            int y = (row * cellHeight);

            SDL_Texture* currentTexture = nullptr;
            int cellType = grid[row][col];

            if(cellType==-1) 
              currentTexture = textures[0];
            else
              currentTexture = textures[1];

            SDL_Rect cellRect = { x, y, cellWidth, cellHeight };
            SDL_RenderCopy(renderer, currentTexture, nullptr, &cellRect);
        }
    }

    //DRAWING THE SHORTEST PATH
    if(!path.empty())
    {
        for (int i = 0; i < path.size(); i++)
        {
            int x = (path[i].second * cellWidth);
            int y = (path[i].first * cellHeight);

            SDL_Rect cellRect = { x, y, cellWidth, cellHeight };

            SDL_RenderDrawLine(renderer, x, y, x, y + cellHeight);
            SDL_RenderDrawLine(renderer, x, y, x + cellWidth, y);
        }
    }

    SDL_RendererFlip flip = SDL_FLIP_NONE; // Default flip
    SDL_RenderCopyEx(renderer, myplayer.texture, NULL, &myplayer.posrec,myplayer.angle, NULL,flip);
    SDL_RenderPresent(renderer);
}

//FUNCTION TO END THE GAME
void Game::cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}