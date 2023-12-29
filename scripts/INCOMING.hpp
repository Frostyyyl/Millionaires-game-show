#pragma once

#include "SDL.h"
#include "object_system.hpp"
#include "texture_manager.hpp"

class Sprite : public Object{
protected: // protected because we need it for spritesheet
    int width, height; 
    SDL_Rect src, dest;
    SDL_Texture* tex;
public:
    Sprite(const char* filename, int x, int y) : Object(x, y){
        tex = TextureManager::LoadTexture(filename);
        SDL_QueryTexture(tex, NULL, NULL, &width, &height);
        src.x = src.y = 0; 
        dest.x = pos.x;
        dest.y = pos.y;
        src.w = dest.w = width;
        src.h = dest.h = height;
    }
    void draw() override{
        TextureManager::Draw(tex, src, dest);
    }
    void update() override{
        // we are not changing sprite's position, so currently blank
    };
    int getSpriteWidth(){
        return width;
    }
    int getSpriteHeight(){
        return height;
    }
    SDL_Rect& getPosition(){ return dest; }
};

class Spritesheet : public Sprite{
private:
    int spritesheetWidth, spritesheetHeight;
    int spriteWidth = width / spritesheetWidth;
    int spriteHeight = height / spritesheetHeight;
public:
    Spritesheet(const char* filename, int x, int y, int spritesheetWidth, int spritesheetHeight) 
    : Sprite(filename, x, y), spritesheetWidth(spritesheetWidth), spritesheetHeight(spritesheetHeight){
        src.x = (spriteWidth) * 0;     // during inicialization we set the sprite to first of a spritesheet  
        src.y = (spriteHeight) * 0;
        src.w = dest.w = spriteWidth;
        src.h = dest.h = spriteHeight;
    }

    // NOTE: when we will decide on the final form of the spritesheets this will probably have to be changed
    void updateSprite(int row = 0, int col = 0){
        src.x = (width / spritesheetWidth) * row;
        src.y = (height / spritesheetHeight) * col;
    }
    int getSpriteWidth(){
        return spriteWidth;
    }
    int getSpriteHeight(){
        return spriteHeight;
    }
};

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
    Button(const char* filename, int x, int y, int spritesheetWidth = 1, int spritesheetHeight = 1)
    : ButtonBase(x, y), spritesheet(filename, x, y, spritesheetWidth, spritesheetHeight){}
    // ^^^ using this constructor we set the button position (separately from spritesheet)
    bool isClicked(int x, int y){
        if(pos.x < x && spritesheet.getSpriteWidth() + pos.x > x && pos.y < y && spritesheet.getSpriteHeight() + pos.y > y){
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