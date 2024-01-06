#include "game_over.hpp"
#include "scene_manager.hpp"


GameOver::GameOver(){}
GameOver::~GameOver(){}

GameOver& GameOver::getInstance(){
    static GameOver INSTANCE;
    return INSTANCE;
}

void GameOver::init (){
}

void GameOver::start(){
}

void GameOver::clean(){
}

void GameOver::processMessage(std::unique_ptr<BaseMessage> msg) {
    //for now also nothing
}