#pragma once
#include <object_system.hpp>
#include <texture_manager.hpp>
#include "position.hpp"

class Sprite : public Object{
private:
    Position pos;
    int width, height; 
    int spritesheetWidth, spritesheetHeight;
    SDL_Rect src, dest;
    SDL_Texture* tex;
public:
    // would be cool if we could get rid of these         V                      V
    Sprite(const char* filename, int x, int y, int spritesheetWidth, int spritesheetHeight) : pos(x, y){
        this->spritesheetWidth = spritesheetWidth;
        this->spritesheetHeight = spritesheetHeight;
        tex = TextureManager::LoadTexture(filename);
        SDL_QueryTexture(tex, NULL, NULL, &width, &height);
        src.x = (width / spritesheetWidth) * 0;    // those zeros represent the spritesheet index of a loaded texture 
        src.y = (height / spritesheetHeight) * 0;  // default is 0
        dest.x = pos.getX();
        dest.y = pos.getY();
        src.w = dest.w = width / spritesheetWidth;
        src.h = dest.h = height / spritesheetHeight;
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