#include "game_over.hpp"
#include "button_system.hpp"
#include "scene_manager.hpp"

Button* retryOverButton = nullptr;

GameOver::GameOver(){}
GameOver::~GameOver(){}

GameOver& GameOver::getInstance(){
    static GameOver INSTANCE;
    return INSTANCE;
}

void GameOver::init (){
    retryOverButton = new Button("images/button_spritesheet.png", 400, 100, 2, 1); 
}

void GameOver::start(){
    SceneManager::getInstance().objectManager.addObject(retryOverButton);
    SceneManager::getInstance().inputManager.addButton(retryOverButton);
}

void GameOver::clean(){
}

void GameOver::processMessage(std::unique_ptr<BaseMessage> msg) {
    //for now also nothing
}