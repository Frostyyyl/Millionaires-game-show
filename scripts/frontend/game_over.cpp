#include "game_over.hpp"
#include "button_system.hpp"
#include "scene_manager.hpp"

Button* retryButtonGameOver = nullptr;
Button* exitButtonGameOver = nullptr;
Sprite* backgroundGameOver = nullptr;

GameOver::GameOver(){}
GameOver::~GameOver(){}

GameOver& GameOver::getInstance(){
    static GameOver INSTANCE;
    return INSTANCE;
}

void GameOver::init (){
    backgroundGameOver = new Sprite("images/game_over_screen.png", 0, 0);
    retryButtonGameOver = new Button("images/retry_button.png", 300, 425, START_GAME); 
    exitButtonGameOver = new Button("images/exit_button.png", 300, 550, EXIT); 
}

void GameOver::start(){
    SceneManager::getInstance().objectManager.addObject(backgroundGameOver);
    SceneManager::getInstance().objectManager.addObject(retryButtonGameOver);
    SceneManager::getInstance().objectManager.addObject(exitButtonGameOver);
    SceneManager::getInstance().inputManager.addButton(retryButtonGameOver);
    SceneManager::getInstance().inputManager.addButton(exitButtonGameOver);
}

void GameOver::clean(){
}

void GameOver::processMessage(std::unique_ptr<BaseMessage> msg) {
    //for now also nothing
}