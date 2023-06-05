#include "Sprite.h"
Sprite::Sprite(string path, SDL_Renderer* renderer) {

    SDL_Surface* temsur = IMG_Load(path.c_str());
    if (temsur == NULL)
        cout << "surface fail" << SDL_GetError() << endl;
    tex = SDL_CreateTextureFromSurface(renderer, temsur);
    if (tex == NULL)
        cout << "surface fail" << SDL_GetError() << endl;
    SDL_FreeSurface(temsur);
}

SDL_Texture* Sprite::gettex() {
    return tex;
}
