#include "input_manager.hpp"
#include "SDL.h"
#include "scene_manager.hpp"
#include <iostream>

void InputManager::update(){
    switch(SceneManager::event.type){
    case SDL_QUIT:
        SceneManager::getInstance().quit();
        break;
    case SDL_MOUSEBUTTONDOWN:
        if(SceneManager::event.button.button == SDL_BUTTON_LEFT){
            for(auto& button : buttons){
                if(button->isClicked(SceneManager::event.button.x, SceneManager::event.button.y)){
                    button->onClick();
                }
            }
        }
        break;
    default:
        break;
    }
}

void InputManager::addButton(ButtonBase* button){
    buttons.emplace_back(button);
}

void InputManager::clear(){
    buttons.clear();
}

void InputManager::erase(ButtonBase* button){
    for (int i = 0; i < buttons.size(); i++){
        if (buttons[i] == button){
            buttons.erase(buttons.begin() + i);
        }
    }
}