#pragma once
#include "object_system.hpp"
#include "sprite_system.hpp"
#include "bridge.hpp"

static bool ANSWER_SELECTED = false;

class ButtonBase : public Object{
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
    Button(const char* filename, int x, int y, int numOfColumns = 2, int numOfRows = 1)
    : ButtonBase(x, y), spritesheet(filename, x, y, numOfColumns, numOfRows){}

    bool isClicked(int x, int y){
        if(pos.x < x && spritesheet.getWidth() + pos.x > x && pos.y < y && spritesheet.getHeight() + pos.y > y){
            return true;
        }
        return false;
    }
    void onClick(){
        std::cout << "Button was clicked " << std::endl; 
    }
    void draw() override{
        spritesheet.draw();
    }
    void update() override{
        // as long as not clicked change accordingly to if we hover or not
        
        if (SDL_HasIntersection(&spritesheet.getPosition(), &Mouse::getPosition())){
            spritesheet.updateSprite(1, 0);
        } else {
            spritesheet.updateSprite(0, 0);
        } 
        
        spritesheet.update();
    }
};

class TextButton : public ButtonBase{
private:
    AnswerSprite spritesheet;
public:
    TextButton(const char* filename, int x, int y, const char* text, int numOfColumns = 2, int numOfRows = 1)
    : ButtonBase(x, y), spritesheet(filename, x, y, text, numOfColumns, numOfRows){}

    bool isClicked(int x, int y){
        if(pos.x < x && spritesheet.getWidth() + pos.x > x && pos.y < y && spritesheet.getHeight() + pos.y > y){
            return true;
        }
        return false;
    }
    void onClick(){
        if (!ANSWER_SELECTED){
            ANSWER_SELECTED = true;
            spritesheet.updateSprite(1, 0);
            Bridge::getInstance().addMessage(FRONT_UPDATE, "Lukasz ssie pale essa");
        }
    }
    void draw() override{
        spritesheet.draw();
    }
    void update() override{
        // as long as not clicked change accordingly to if we hover or not
        if (!ANSWER_SELECTED){
            if (SDL_HasIntersection(&spritesheet.getPosition(), &Mouse::getPosition())){
                spritesheet.updateSprite(1, 0);
            } else {
                spritesheet.updateSprite(0, 0);
            } 
        }
        spritesheet.update();
    }
};