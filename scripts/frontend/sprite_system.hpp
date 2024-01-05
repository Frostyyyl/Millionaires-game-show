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

class QuestionSprite : public Spritesheet{
private: 
    Text question;
    TTF_Font* font;
    SDL_Texture* textTexture;
    static const int MOVE_HORIZONTALLY = 5;
    static const int MOVE_VERTICALLY = -4;
public:
    QuestionSprite(const char* filename, int x, int y, const char* questionText, int numOfColumns = 1, int numOfRows = 1) 
            : Spritesheet(filename, x, y, numOfColumns, numOfRows){
        
        question.dest.x += MOVE_HORIZONTALLY;
        
        loadQuestion(questionText);
    }
    void loadQuestion(const char* answerText){
        question.text = answerText;

        font = textManager.getFont46();
        TTF_SizeText(font, question.text.c_str(), &question.dest.w, &question.dest.h);
        if (question.dest.w > dest.w - MOVE_HORIZONTALLY * 2){
            font = textManager.getFont30();
            TTF_SizeText(font, question.text.c_str(), &question.dest.w, &question.dest.h);
            if (question.dest.w > (dest.w - MOVE_HORIZONTALLY * 2) * 2 - 50){
                font = textManager.getFont21();
                TTF_SizeText(font, question.text.c_str(), &question.dest.w, &question.dest.h);
            }
            if (question.dest.w > dest.w - MOVE_HORIZONTALLY * 2){
                question.dest.w = dest.w - MOVE_HORIZONTALLY * 2;
                question.dest.h *= 2;
            }
        }
        // center the text (depending on the font might have to change the value of MOVE_VERTICALLY)
        question.dest.y = (dest.h / 2) - (question.dest.h / 2) + MOVE_VERTICALLY;

        textTexture = textManager.loadText(font, question, dest);
    }
    void draw() override{
        TextureManager::Draw(tex, src, dest);
        textManager.draw(textTexture, dest);
    }
};

class AnswerSprite : public Spritesheet{
private:
    Text answer;
    Text character;
    TTF_Font* font;
    SDL_Texture* textTexture;
    static const int ALIGN = 3;
    static const int MOVE_HORIZONTALLY = 5;
    static const int MOVE_VERTICALLY = -3;
public:
    AnswerSprite(const char* filename, int x, int y, const char* answerText, const char* symbol, int numOfColumns = 1, int numOfRows = 1) 
            : Spritesheet(filename, x, y, numOfColumns, numOfRows){
    
        character.text = symbol + (std::string)":";

        TTF_SizeText(textManager.getFont21(), character.text.c_str(), &character.dest.w, &character.dest.h);
        character.dest.x += MOVE_HORIZONTALLY;
        character.dest.y += (dest.h / 2) - (character.dest.h / 2) + MOVE_VERTICALLY;
        answer.dest.x += MOVE_HORIZONTALLY * 2 + character.dest.w;

        loadAnswer(answerText);
    }
    void loadAnswer(const char* answerText){
        answer.text = answerText;

        font = textManager.getFont21();
        TTF_SizeText(font, answer.text.c_str(), &answer.dest.w, &answer.dest.h);
        if (answer.dest.w > dest.w - MOVE_HORIZONTALLY * 3 - character.dest.w){
            font = textManager.getFont16();
            TTF_SizeText(font, answer.text.c_str(), &answer.dest.w, &answer.dest.h);
        }
        // center the text (depending on the font might have to change the value of MOVE_VERTICALLY)
        answer.dest.y = (dest.h / 2) - (answer.dest.h / 2) + MOVE_VERTICALLY;
    
        textTexture = textManager.loadText(font, answer, character, dest);
    }

    void draw() override{
        TextureManager::Draw(tex, src, dest);
        textManager.draw(textTexture, dest);
    }
};