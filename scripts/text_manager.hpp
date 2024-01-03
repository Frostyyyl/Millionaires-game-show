#pragma once
#include "SDL.h"
#include "SDL_TTF.h"

class TextManager{
public:
    static TTF_Font* LoadFont(const char* font_filename, int font_size){
        TTF_Font* font = TTF_OpenFont(font_filename, font_size);
        if (!font) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        }
        return font;
    }
};