#pragma once

#include <iostream>
#include <vector>
#include "SDL.h"
#include "game.hpp"
#include "button_object.hpp"

class InputManager{
private:
    std::vector<Button*> buttons;
public:
    void update(){
        switch(Game::event.type){
        case SDL_QUIT:
            std::cout << "aaaa" << std::endl; //i tried to quit game but can't reference game right...
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(Game::event.button.button == SDL_BUTTON_LEFT){
                for(auto& button : buttons){
                    if(button->isClicked(Game::event.button.x, Game::event.button.y)){
                        button->onClick();
                    }
                }
            }
            break;
        default:
            break;
        }
    }
    void addButton(Button* button){
        buttons.emplace_back(button);
    }
};