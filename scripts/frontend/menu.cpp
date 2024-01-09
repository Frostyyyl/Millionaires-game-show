#include "menu.hpp"
#include "button_system.hpp"
#include "scene_manager.hpp"

Button* playButtonMenu = nullptr;
Button* exitButtonMenu = nullptr;
Sprite* backgroundMenu = nullptr;

MainMenu::MainMenu(){}
MainMenu::~MainMenu(){}

MainMenu& MainMenu::getInstance(){
    static MainMenu INSTANCE;
    return INSTANCE;
}

void MainMenu::init (){
    backgroundMenu = new Sprite("images/background.png", 0, 0);
    playButtonMenu = new Button("images/button_spritesheet.png", 395, 400, START_GAME); 
    exitButtonMenu = new Button("images/exit_button.png", 395, 550, EXIT); 
}

void MainMenu::start(){
    SceneManager::getInstance().objectManager.addObject(backgroundMenu);
    SceneManager::getInstance().objectManager.addObject(playButtonMenu);
    SceneManager::getInstance().objectManager.addObject(exitButtonMenu);
    SceneManager::getInstance().inputManager.addButton(playButtonMenu);
    SceneManager::getInstance().inputManager.addButton(exitButtonMenu);
}

void MainMenu::clean(){
}

void MainMenu::processMessage(std::unique_ptr<BaseMessage> msg) {
    // main menu i think doesnt get any messages
}