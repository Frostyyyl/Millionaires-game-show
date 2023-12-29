#pragma once

#include "SDL.h"
#include "object_system.hpp"

class Mouse : public Object{
private:
    static SDL_Rect pointer;
public:
    Mouse(){
        pointer.w = pointer.h = 1;
    };
    void update(){
        SDL_GetMouseState(&pointer.x, &pointer.y); 
    }
    void draw(){};
    static SDL_Rect& getPosition(){ return pointer; }
};