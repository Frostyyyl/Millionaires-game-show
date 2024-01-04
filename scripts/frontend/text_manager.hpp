#pragma once
#include "SDL.h"
#include "SDL_TTF.h"

class TextManager{
private:
    const std::string fontFilename = "fonts/muli.ttf";
    TTF_Font* font46;
    TTF_Font* font32;
    TTF_Font* font21;
public:
    static TTF_Font* LoadFont(const char* fontFilename, int fontSize){
        TTF_Font* font = TTF_OpenFont(fontFilename, fontSize);
        if (!font) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        }
        return font;
    }
    void init(){
        font46 = LoadFont(fontFilename.c_str(), 46);
        font32 = LoadFont(fontFilename.c_str(), 32);
        font21 = LoadFont(fontFilename.c_str(), 21);
    }
    TTF_Font* getFont46(){ return font46; }
    TTF_Font* getFont32(){ return font32; }
    TTF_Font* getFont21(){ return font21; }

};

TextManager textManager;