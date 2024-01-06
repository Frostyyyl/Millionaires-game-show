#pragma once
#include "SDL_image.h"
#include "scene_manager.hpp"

class TextureManager{
public:
    static SDL_Texture* LoadTexture(const char* filename){
        SDL_Surface* tempSurface = IMG_Load(filename);
        SDL_Texture* tex = SDL_CreateTextureFromSurface(SceneManager::renderer, tempSurface);
        if(tex == nullptr){
            std::cerr << "Couldn't load texture" << std::endl;
            exit(1);
        }
        SDL_FreeSurface(tempSurface);

        return tex;
    }
    static void Draw(SDL_Texture* tex, SDL_Rect &src, SDL_Rect &dest){
        SDL_RenderCopy(SceneManager::renderer, tex, &src, &dest);
    }
};