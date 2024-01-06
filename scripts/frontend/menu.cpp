#include "menu.hpp"
#include "button_system.hpp"
#include "scene_manager.hpp"

Button* playButton = nullptr;

MainMenu::MainMenu(){}
MainMenu::~MainMenu(){}

MainMenu& MainMenu::getInstance(){
    static MainMenu INSTANCE;
    return INSTANCE;
}

void MainMenu::init (){
    playButton = new Button("images/button_spritesheet.png", 69, 69, 2, 1); 
}

void MainMenu::start(){
    SceneManager::getInstance().objectManager.addObject(playButton);
    SceneManager::getInstance().inputManager.addButton(playButton);
}

void MainMenu::clean(){
}

void MainMenu::processMessage(std::unique_ptr<BaseMessage> msg) {
    // main menu i think doesnt get any messages
}