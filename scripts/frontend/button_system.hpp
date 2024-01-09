#pragma once
#include "sprite_system.hpp"
#include "bridge.hpp"

static bool ANSWER_SELECTED = false;

enum ButtonFunction {START_GAME, PHONE, AUDIENCE, FIFTY_FIFTY, EXIT};

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
    ButtonFunction id;
public:
    Button(const char* filename, int x, int y, ButtonFunction id, int numOfColumns = 2, int numOfRows = 1)
    : ButtonBase(x, y), spritesheet(filename, x, y, numOfColumns, numOfRows), id(id){}

    bool isClicked(int x, int y){
        if(pos.x < x && spritesheet.getWidth() + pos.x > x && pos.y < y && spritesheet.getHeight() + pos.y > y){
            return true;
        }
        return false;
    }
    void onClick(){
        switch (id)
        {
        case START_GAME:
            Bridge::getInstance().addMessage(BACK_START_GAME);
            break;
        case FIFTY_FIFTY:
            Bridge::getInstance().addMessage(BACK_50_50);
            break;
        case PHONE:
            Bridge::getInstance().addMessage(BACK_PHONE);
            break;
        case AUDIENCE:
            Bridge::getInstance().addMessage(BACK_AUDIENCE);
            break;
        case EXIT:
            Bridge::getInstance().addMessage(FRONT_EXIT);
            break;
        default:
            std::cerr << "Failed to press a button" << std::endl;
            break;
        }
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
        this->~Button();
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
        this->~TextButton();
    }
};