#pragma once
#include <object_system.hpp>
#include <texture_manager.hpp>
#include "position.hpp"
#include <iostream>

class Sprite : public Object{
private:
    Position pos;
    SDL_Rect src, dest;
    SDL_Texture* tex;
public:
    Sprite(const char* filename, int x, int y) : pos(x, y){
        tex = TextureManager::LoadTexture(filename);
        src.x = dest.x = pos.getX();
        src.y = dest.y = pos.getY();
        src.w = dest.w = 564;
        src.h = dest.h = 564;
    }
    /* this is probably not needed now
    Sprite(int x, int y) : pos(x, y){
        src.x = dest.x = pos.getX();
        src.y = dest.y = pos.getY();
        src.w = dest.w = 564;
        src.h = dest.h = 564;
    }*/
    // void init(const char* filename){
    //     tex = TextureManager::LoadTexture(filename);
    // }
    void draw() override{
        TextureManager::Draw(tex, src, dest);
    }
    void update() override{
        dest.x = pos.getX();
        dest.y = pos.getY();
    };
};