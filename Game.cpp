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
            //if (i<=9&&j>20&&j<24||i>9&&i<13&&j>=5&&j<24||i>=13&&j>=5&&j<9)
                grid[i][j] = 1;
           // cout << grid[i][j];
        }
       // cout <<endl;
    }
    texturePaths = {
        "textures/stone.bmp",
        "textures/blackstone2.bmp",        
    };
    
    keys = SDL_GetKeyboardState(NULL);
    offset.first = 0;
    offset.second = 0;
    //cout << "enter cord" << endl;
    //cin >> de_pos.first >> de_pos.second;
}
void Game::shortestpath(int p_x, int p_y, int d_x, int d_y)
{
    priority_queue<pair<int,int>>q;
    
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
                if (myplayer.p_pos.second > 25 && grid[(int)((myplayer.p_pos.second+5) / 25)][(int)(myplayer.p_pos.first / 25)] != 0)
                {
                    myplayer.p_pos.second -= myplayer.speed;
                    offset.second -= myplayer.speed;
                    myplayer.previousDirection = myplayer.currentDirection;
                    myplayer.currentDirection = Player::FacingDirection::Up;
                    myplayer.change = true;
                    cout << myplayer.previousDirection << " " << myplayer.currentDirection << " " << myplayer.angle << endl;
                }
            }
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                if(myplayer.p_pos.second <600&& grid[(int)((myplayer.p_pos.second +35) / 25)][(int)(myplayer.p_pos.first / 25)] != 0)
                {
                    myplayer.p_pos.second += myplayer.speed;
                    offset.second += myplayer.speed;
                    myplayer.previousDirection = myplayer.currentDirection;
                    myplayer.currentDirection = Player::FacingDirection::Down;
                    myplayer.change = true;
                    cout << myplayer.previousDirection << " " << myplayer.currentDirection << " " << myplayer.angle << endl;
                }
            }
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                if(myplayer.p_pos.first >25 && grid[(int)(myplayer.p_pos.second / 25)][(int)((myplayer.p_pos.first +5) / 25)] !=0)
                {
                    myplayer.p_pos.first -= myplayer.speed;
                    offset.first -= myplayer.speed; // Adjust the X offset when moving left
                    myplayer.previousDirection = myplayer.currentDirection;
                    myplayer.currentDirection = Player::FacingDirection::Left;
                    myplayer.change = true;
                    cout << myplayer.previousDirection << " " << myplayer.currentDirection << " "<<myplayer.angle<<endl;
                }
            }
            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                if(myplayer.p_pos.first <800&& grid[(int)(myplayer.p_pos.second / 25)][(int)((myplayer.p_pos.first +25 ) / 25)] != 0)
                {
                    myplayer.p_pos.first += myplayer.speed;
                    offset.first += myplayer.speed; // Adjust the X offset when moving right
                    myplayer.previousDirection = myplayer.currentDirection;
                    myplayer.currentDirection = Player::FacingDirection::Right;
                    myplayer.change = true;
                    cout << myplayer.previousDirection << " " << myplayer.currentDirection << " " << myplayer.angle << endl;
                }
            }

        }
    }
}
void Game::update()
{
    myplayer.posrec.x = myplayer.p_pos.first - offset.first;
    myplayer.posrec.y = myplayer.p_pos.second - offset.second;
    //shortestpath(myplayer.p_pos.second / 25, myplayer.p_pos.first / 25, (de_pos.second + offset.second) / 25, (de_pos.first + offset.first) / 25);
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
            int x = (col * cellWidth) - offset.first;
            int y = (row * cellHeight) - offset.second;

            SDL_Texture* currentTexture = nullptr;
            int cellType = grid[row][col]; 
           if(cellType==0) 
              currentTexture = textures[0];
           else
              currentTexture = textures[1];
            SDL_Rect cellRect = { x, y, cellWidth, cellHeight };
            SDL_RenderCopy(renderer, currentTexture, nullptr, &cellRect);
        }
    }
    SDL_RendererFlip flip = SDL_FLIP_NONE; // Default flip
    SDL_RenderCopyEx(renderer, myplayer.texture, NULL, &myplayer.posrec,myplayer.angle, NULL,flip);
    SDL_RenderCopy(renderer, enemy.texture, NULL, &enemy.posrec);
    SDL_RenderPresent(renderer);
}
void Game::cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}