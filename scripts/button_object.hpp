#pragma once
#include "object_system.hpp"
#include "sprite_system.hpp"


class ButtonBase : public Object{
protected:
    bool isSelected = false;
public:
    ButtonBase(){}
    ButtonBase(int x, int y) : Object(x, y){}
    virtual bool isClicked(int x, int y) = 0;
    virtual void onClick() = 0;
};

class Button : public ButtonBase{
private:
    Spritesheet spritesheet;
public:
    Button(const char* filename, int x, int y, int numOfColumns = 1, int numOfRows = 1)
    : ButtonBase(x, y), spritesheet(filename, x, y, numOfColumns, numOfRows){}
    // ^^^ using this constructor we set the button position (separately from spritesheet)
    bool isClicked(int x, int y){
        if(pos.x < x && spritesheet.getWidth() + pos.x > x && pos.y < y && spritesheet.getHeight() + pos.y > y){
            return true;
        }
        return false;
    }
    void onClick(){
        isSelected = true;
        spritesheet.updateSprite(1, 0);
    }
    void draw() override{
        spritesheet.draw();
    }
    void update() override{
        // as long as not clicked change accordingly to if we hover or not
        if (!isSelected){
            if (SDL_HasIntersection(&spritesheet.getPosition(), &Mouse::getPosition())){
                spritesheet.updateSprite(1, 0);
            } else {
                spritesheet.updateSprite(0, 0);
            } 
        }
        spritesheet.update();
    }
};