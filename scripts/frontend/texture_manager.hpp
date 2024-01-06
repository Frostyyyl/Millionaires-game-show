#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "game.hpp"

class TextureManager{
public:
    static SDL_Texture* LoadTexture(const char* filename){
        SDL_Surface* tempSurface = IMG_Load(filename);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
        if(tex == nullptr){
            std::cerr << "Couldn't load texture" << std::endl;
            exit(1);
        }
        SDL_FreeSurface(tempSurface);

        return tex;
    }
    static void Draw(SDL_Texture* tex, SDL_Rect &src, SDL_Rect &dest){
        SDL_RenderCopy(Game::renderer, tex, &src, &dest);
    }
};