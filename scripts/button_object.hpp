#pragma once
#include "object_system.hpp"
#include "texture_manager.hpp"
#include "sprite_object.hpp"
#include "position.hpp"

//not polimorphism but inheritance from sprite (i think it's better that way)
class Button : public Spritesheet{
private:
    bool isSelected = false;
public:
    Button(const char* filename, int x, int y, int spritesheetWidth = 1, int spritesheetHeight = 1)
        : Spritesheet(filename, x, y, spritesheetWidth, spritesheetHeight){}

    bool isClicked(int x, int y){
        if(pos.getX() < x && width + pos.getX() > x && pos.getY() < y && height + pos.getY() > y){
            return true;
        }
        return false;
    }

    void onClick(){ // i have no idea for this part yet hehe
        // play some dramatic music
        // wait
        // show answer
        // wait
        // next question / gameover
        isSelected = true;
        updateSprite(1, 0);
    }

    void update() override{
        // as long as not clicked change accordingly to if we hover or not
        if (!isSelected){
            // LUKASZ: i can make a mouse class if we want to
            SDL_Rect mouse;
            SDL_GetMouseState(&mouse.x, &mouse.y); 
            // there is a function SDL_HasIntersection to compare two SDL_RECT, should probably change to that 
            // (didn't work and i had no time 🤪)
            if (pos.getX() < mouse.x && (width / spritesheetWidth) + pos.getX() > mouse.x && 
                pos.getY() < mouse.y && (height / spritesheetHeight) + pos.getY() > mouse.y){
                updateSprite(1, 0);
            } else {
                updateSprite(0, 0);
            }
        }
        dest.x = pos.getX();
        dest.y = pos.getY();
    }
};