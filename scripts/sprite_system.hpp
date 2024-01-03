#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "object_system.hpp"
#include "text_manager.hpp"
#include "texture_manager.hpp"


class Sprite : public Object{
protected: // protected because we need it for spritesheet
    int width, height; 
    SDL_Rect src, dest;
    SDL_Texture* tex;
public:
    Sprite(const char* filename, int x, int y) : Object(x, y){
        tex = TextureManager::LoadTexture(filename);
        SDL_QueryTexture(tex, NULL, NULL, &width, &height);
        src.x = src.y = 0; 
        dest.x = pos.x;
        dest.y = pos.y;
        src.w = dest.w = width;
        src.h = dest.h = height;
    }
    void draw() override{
        TextureManager::Draw(tex, src, dest);
    }
    void update() override{
        // we are not changing sprite's position, so currently blank
    };
    int getWidth(){
        return width;
    }
    int getHeight(){
        return height;
    }
    SDL_Rect& getPosition(){ return dest; }
};

class Spritesheet : public Sprite{
private:
    int numOfColumns, numOfRows;
    int spriteWidth = width / numOfColumns;
    int spriteHeight = height / numOfRows;
public:
    Spritesheet(const char* filename, int x, int y, int numOfColumns, int numOfRows) 
    : Sprite(filename, x, y), numOfColumns(numOfColumns), numOfRows(numOfRows){
        src.x = (spriteWidth) * 0;     // during inicialization we set the sprite to first of a spritesheet  
        src.y = (spriteHeight) * 0;
        src.w = dest.w = spriteWidth;
        src.h = dest.h = spriteHeight;
    }

    // NOTE: when we will decide on the final form of the spritesheets this will probably have to be changed
    void updateSprite(int row = 0, int col = 0){
        src.x = (width / numOfColumns) * row;
        src.y = (height / numOfRows) * col;
    }
    int getWidth(){
        return spriteWidth;
    }
    int getHeight(){
        return spriteHeight;
    }
};

class TextSprite : public Spritesheet{
private:
    std::string text;
    TTF_Font* font;
public:
    TextSprite(const char* filename, int x, int y, const char* font_filename , const char* text, int numOfColumns, int numOfRows) 
            : Spritesheet(filename, x, y, numOfColumns, numOfRows), text(text){
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
