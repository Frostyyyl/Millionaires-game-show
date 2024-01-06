#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "object_system.hpp"
#include "text_manager.hpp"
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
    int getWidth(){
        return width;
    }
    int getHeight(){
        return height;
    }
    SDL_Rect& getPosition(){ return dest; }
};

class Spritesheet : public Sprite{
private:
    int numOfColumns, numOfRows;
    int spriteWidth = width / numOfColumns;
    int spriteHeight = height / numOfRows;
public:
    Spritesheet(const char* filename, int x, int y, int numOfColumns = 2, int numOfRows = 1) 
    : Sprite(filename, x, y), numOfColumns(numOfColumns), numOfRows(numOfRows){
        src.x = (spriteWidth) * 0;     // during inicialization we set the sprite to first of a spritesheet  
        src.y = (spriteHeight) * 0;
        src.w = dest.w = spriteWidth;
        src.h = dest.h = spriteHeight;
    }
    // NOTE: when we will decide on the final form of the spritesheets this will probably have to be changed
    void updateSprite(int row = 0, int col = 0){
        src.x = (width / numOfColumns) * row;
        src.y = (height / numOfRows) * col;
    }
    int getWidth(){
        return spriteWidth;
    }
    int getHeight(){
        return spriteHeight;
    }
};

class TextSprite : public Spritesheet{
private: 
    Text contents;
    TTF_Font* font;
    SDL_Texture* textTexture;
    static const int MOVE_HORIZONTALLY = 5;
    static const int MOVE_VERTICALLY = -4;
public:
    TextSprite(const char* filename, int x, int y, std::string data, int numOfColumns = 1, int numOfRows = 1) 
            : Spritesheet(filename, x, y, numOfColumns, numOfRows){
        
        contents.dest.x += MOVE_HORIZONTALLY;
        
        loadData(data);
    }
    void loadData(std::string data){
        contents.text = data;

        font = textManager.getHugeFont();
        TTF_SizeText(font, contents.text.c_str(), &contents.dest.w, &contents.dest.h);
        if (contents.dest.w > dest.w - MOVE_HORIZONTALLY * 2){
            font = textManager.getLargeFont();
            TTF_SizeText(font, contents.text.c_str(), &contents.dest.w, &contents.dest.h);
            if (contents.dest.w > (dest.w - MOVE_HORIZONTALLY * 2) * 2 - 50){
                font = textManager.getMediumFont();
                TTF_SizeText(font, contents.text.c_str(), &contents.dest.w, &contents.dest.h);
            }
            if (contents.dest.w > dest.w - MOVE_HORIZONTALLY * 2){
                contents.dest.w = dest.w - MOVE_HORIZONTALLY * 2;
                contents.dest.h *= 2;
            }
        }
        // center the text (depending on the font might have to change the value of MOVE_VERTICALLY)
        contents.dest.y = (dest.h / 2) - (contents.dest.h / 2) + MOVE_VERTICALLY;

        textTexture = textManager.loadText(font, contents, dest);
    }
    void draw() override{
        TextureManager::Draw(tex, src, dest);
        textManager.draw(textTexture, dest);
    }
};

class DoubleTextsprite : public Spritesheet{
private:
    std::string flush;
    Text contents;
    Text prefix;
    TTF_Font* font;
    SDL_Texture* textTexture;
    static const int ALIGN = 3;
    static const int MOVE_HORIZONTALLY = 5;
    static const int MOVE_VERTICALLY = -3;
public:
    DoubleTextsprite(const char* filename, int x, int y, std::string prefixData, std::string data, std::string flush = "left",
                    int numOfColumns = 1, int numOfRows = 1) : Spritesheet(filename, x, y, numOfColumns, numOfRows), flush(flush){
        prefix.text = prefixData;

        TTF_SizeText(textManager.getMediumFont(), prefix.text.c_str(), &prefix.dest.w, &prefix.dest.h);
        prefix.dest.x += MOVE_HORIZONTALLY;
        prefix.dest.y += (dest.h / 2) - (prefix.dest.h / 2) + MOVE_VERTICALLY;
        contents.dest.x += MOVE_HORIZONTALLY * 2 + prefix.dest.w;

        loadData(data);
    }
    void loadData(std::string data){
        contents.text = data;

        font = textManager.getMediumFont();
        TTF_SizeText(font, contents.text.c_str(), &contents.dest.w, &contents.dest.h);
        if (contents.dest.w > dest.w - MOVE_HORIZONTALLY * 3 - prefix.dest.w){
            font = textManager.getSmallFont();
            TTF_SizeText(font, contents.text.c_str(), &contents.dest.w, &contents.dest.h);
        }
        // center the text (depending on the font might have to change the value of MOVE_VERTICALLY)
        contents.dest.y = (dest.h / 2) - (contents.dest.h / 2) + MOVE_VERTICALLY;
        if (font == textManager.getSmallFont()){
            contents.dest.y += ALIGN;
        }
        if (flush == "right"){
            contents.dest.x = dest.w - contents.dest.w - MOVE_HORIZONTALLY;
        }
    
        textTexture = textManager.loadText(font, contents, prefix, dest);
    }
    void draw() override{
        TextureManager::Draw(tex, src, dest);
        textManager.draw(textTexture, dest);
    }
};