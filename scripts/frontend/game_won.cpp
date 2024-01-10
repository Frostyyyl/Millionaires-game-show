#include "game_won.hpp"
#include "button_system.hpp"
#include "scene_manager.hpp"

Button* retryButtonGameWon = nullptr;
Button* exitButtonGameWon = nullptr;
Sprite* backgroundGameWon = nullptr;

GameWon::GameWon(){}
GameWon::~GameWon(){}

GameWon& GameWon::getInstance(){
    static GameWon INSTANCE;
    return INSTANCE;
}

void GameWon::init (){
    backgroundGameWon = new Sprite("images/game_won_screen.png", 0, 0);
    retryButtonGameWon = new Button("images/play_again_button.png", 300, 425, START_GAME); 
    exitButtonGameWon = new Button("images/exit_button.png", 300, 550, EXIT); 
}

void GameWon::start(){
    SceneManager::getInstance().objectManager.addObject(backgroundGameWon);
    SceneManager::getInstance().objectManager.addObject(retryButtonGameWon);
    SceneManager::getInstance().objectManager.addObject(exitButtonGameWon);
    SceneManager::getInstance().inputManager.addButton(retryButtonGameWon);
    SceneManager::getInstance().inputManager.addButton(exitButtonGameWon);
}

void GameWon::clean(){
}

void GameWon::processMessage(std::unique_ptr<BaseMessage> msg) {
    //for now also nothing
}