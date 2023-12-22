#pragma once
#include "object_system.hpp"
#include "texture_manager.hpp"
#include "sprite_object.hpp"
#include "position.hpp"

//not polimorphism but inheritance from sprite (i think it's better that way)
class Button : public Sprite{
public:
    //goofy for now sorry
    Button(const char* filename, int x, int y, int spritesheetWidth = 1, int spritesheetHeight = 1):
    Sprite(filename, x, y, spritesheetWidth, spritesheetHeight){}

    bool isClicked(int x, int y){
        if(pos.getX() < x && width + pos.getX() > x && pos.getY() < y && height + pos.getY() > y){
            return true;
        }
        return false;
    }

    void onClick(){ //i have no idea for this part yet hehe
        std::cout << "It was clicked x = " << pos.getX() << std::endl;
    }
};