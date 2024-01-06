#pragma once
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
        Bridge::getInstance().addMessage(BACK_START_GAME);
    }
    void draw() override{
        spritesheet.draw();
    }
    void update() override{
        if (SDL_HasIntersection(&spritesheet.getPosition(), &Mouse::getPosition())){
            spritesheet.updateSprite(1, 0);
        } else {
            spritesheet.updateSprite(0, 0);
        } 
        spritesheet.update();
    }
    void destroy(){
        spritesheet.destroy();
        this->destroy();
    }
};

class TextButton : public ButtonBase{
private:
    DoubleTextsprite spritesheet;
    int id;
public:
    TextButton(const char* filename, int x, int y, std::string prefixData, std::string data, int id, std::string flush = "left", 
                int numOfColumns = 2, int numOfRows = 1): ButtonBase(x, y),
                spritesheet(filename, x, y, prefixData, data, flush, numOfColumns, numOfRows), id(id){}
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
            Bridge::getInstance().addMessage(BACK_ANSWER, id);
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
    void loadData(std::string data){
        spritesheet.loadData(data);
    }
    void destroy(){
        spritesheet.destroy();
        this->destroy();
    }
};