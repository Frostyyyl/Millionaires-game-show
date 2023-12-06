#include "texture_manager.hpp"

SDL_Texture* TextureManager::LoadTexture(const char* filename){
    SDL_Surface* tempSurface = IMG_Load(filename);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    if(tex == nullptr){
        std::cerr << "sperma twojej matki" << std::endl;
        exit(1);
    }
    SDL_FreeSurface(tempSurface);

    return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest){
    SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}