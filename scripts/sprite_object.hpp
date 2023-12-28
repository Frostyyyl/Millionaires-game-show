#pragma once
#include "object_system.hpp"
#include "texture_manager.hpp"
#include "position.hpp"

class Sprite : public Object{
protected: //protected cause i need it for button
    Position pos;
    int width, height; 
    SDL_Rect src, dest;
    SDL_Texture* tex;
public:
    Sprite(const char* filename, int x, int y) : pos(x, y){
        tex = TextureManager::LoadTexture(filename);
        SDL_QueryTexture(tex, NULL, NULL, &width, &height);
        src.x = src.y = 0; 
        dest.x = pos.getX();
        dest.y = pos.getY();
        src.w = dest.w = width;
        src.h = dest.h = height;
    }
    /* this is probably not needed now
    Sprite(int x, int y) : pos(x, y){
        src.x = dest.x = pos.getX();
        src.y = dest.y = pos.getY();
        src.w = dest.w = 564;
        src.h = dest.h = 564;
    }
    void init(const char* filename){
        tex = TextureManager::LoadTexture(filename);
    } */
    void draw() override{
        TextureManager::Draw(tex, src, dest);
    }
    void update() override{
        dest.x = pos.getX();
        dest.y = pos.getY();
    };
};

class Spritesheet : public Object{
protected:
    Position pos;
    int width, height; 
    int spritesheetWidth, spritesheetHeight;
    SDL_Rect src, dest;
    SDL_Texture* tex;
public:
    Spritesheet(const char* filename, int x, int y, int spritesheetWidth, int spritesheetHeight) 
    : pos(x, y), spritesheetWidth(spritesheetWidth), spritesheetHeight(spritesheetHeight){
        tex = TextureManager::LoadTexture(filename);
        SDL_QueryTexture(tex, NULL, NULL, &width, &height);
        src.x = (width / spritesheetWidth) * 0;     // during inicialization we set the sprite to first of a spritesheet  
        src.y = (height / spritesheetHeight) * 0;
        dest.x = pos.getX();
        dest.y = pos.getY();
        src.w = dest.w = width / spritesheetWidth;
        src.h = dest.h = height / spritesheetHeight;
    }
    void draw() override{
        TextureManager::Draw(tex, src, dest);
    }
    void update() override{
        dest.x = pos.getX();
        dest.y = pos.getY();
    }

    // NOTE: when we will decide on the final form of the spritesheets this will probably have to be changed
    void updateSprite(int row = 0, int col = 0){
        src.x = (width / spritesheetWidth) * row;
        src.y = (height / spritesheetHeight) * col;
    }
};