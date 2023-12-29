#pragma once
#include "text_manager.hpp"
#include "sprite_system.hpp"
#include "SDL_ttf.h"

class TextSprite : public Spritesheet{
private:
    std::string text;
    TTF_Font* font;
public:
    TextSprite(const char* filename, int x, int y, const char* font_filename , const char* text, int spritesheetWidth = 1, int spritesheetHeight = 1) 
            : Spritesheet(filename, x, y, spritesheetWidth, spritesheetHeight), text(text){
        font = TextManager::LoadFont(font_filename, 20);
    }
    void drawText() {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
        if (!textSurface) {
            std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        }
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
        if (!textTexture) {
            std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        }
        SDL_RenderCopy(Game::renderer, textTexture, &src, &dest);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
    void draw() override{
        TextureManager::Draw(tex, src, dest);
        drawText();
    }
};
