#include "game_won.hpp"
#include "button_system.hpp"
#include "scene_manager.hpp"

Button* retryButton = nullptr;

GameWon::GameWon(){}
GameWon::~GameWon(){}

GameWon& GameWon::getInstance(){
    static GameWon INSTANCE;
    return INSTANCE;
}

void GameWon::init (){
    retryButton = new Button("images/button_spritesheet.png", 400, 400, 2, 1); 
}

void GameWon::start(){
    SceneManager::getInstance().objectManager.addObject(retryButton);
    SceneManager::getInstance().inputManager.addButton(retryButton);
}

void GameWon::clean(){
}

void GameWon::processMessage(std::unique_ptr<BaseMessage> msg) {
    //for now also nothing
}