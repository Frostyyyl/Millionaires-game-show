#pragma once
#include "SDL.h"
#include "SDL_TTF.h"

struct Text{
    std::string text;
    SDL_Rect dest = {0, 0, 0, 0};

    Text(){}
};

class TextManager{
private:
    const std::string fontFilename = "fonts/muli.ttf";
    TTF_Font* hugeFont;
    TTF_Font* largeFont;
    TTF_Font* mediumFont;
    TTF_Font* smallFont;
public:
    TTF_Font* loadFont(const char* fontFilename, int fontSize){
        TTF_Font* font = TTF_OpenFont(fontFilename, fontSize);
        if (!font) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        }
        return font;
    }
    SDL_Texture* loadText(TTF_Font* font, Text &text, Text &symbol, SDL_Rect &dest){
        SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, dest.w, dest.h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
        SDL_Surface* charSurface = TTF_RenderText_Blended_Wrapped(mediumFont, symbol.text.c_str(), {255, 15, 76}, symbol.dest.w);
        SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text.text.c_str(), {12, 12, 12}, text.dest.w);
        if (!tempSurface){
            std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        } if (!textSurface) {
            std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        } if (!charSurface) {
            std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        }
        if (SDL_BlitSurface(charSurface, NULL, tempSurface, &symbol.dest) == -1){
            std::cerr << "Failed to merge surfaces"; 
        } if (SDL_BlitSurface(textSurface, NULL, tempSurface, &text.dest) == -1){
            std::cerr << "Failed to merge surfaces" << std::endl;
        }
        SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
        if (!tex) {
            std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(tempSurface);
        SDL_FreeSurface(charSurface);
        SDL_FreeSurface(textSurface);

        return tex;
    }
    SDL_Texture* loadText(TTF_Font* font, Text &text, SDL_Rect &dest){
        SDL_Surface* tempSurface = SDL_CreateRGBSurface(0, dest.w, dest.h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
        SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped(font, text.text.c_str(), {12, 12, 12}, text.dest.w);
        if (!tempSurface) {
            std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        } if (!textSurface) {
            std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
        }
        if (SDL_BlitSurface(textSurface, NULL, tempSurface, &text.dest) == -1){
            std::cerr << "Failed to merge surfaces"; 
        }
        SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
        if (!tex) {
            std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(tempSurface);
        SDL_FreeSurface(textSurface);

        return tex;
    }
    void draw(SDL_Texture* tex, SDL_Rect &dest){
        SDL_RenderCopy(Game::renderer, tex, NULL, &dest); 
    }
    void init(){
        hugeFont = loadFont(fontFilename.c_str(), 46);
        largeFont = loadFont(fontFilename.c_str(), 32);
        mediumFont = loadFont(fontFilename.c_str(), 21);
        smallFont = loadFont(fontFilename.c_str(), 16);
    }
    TTF_Font* getHugeFont(){ return hugeFont; }
    TTF_Font* getLargeFont(){ return largeFont; }
    TTF_Font* getMediumFont(){ return mediumFont; }
    TTF_Font* getSmallFont(){ return smallFont; }

};

TextManager textManager;