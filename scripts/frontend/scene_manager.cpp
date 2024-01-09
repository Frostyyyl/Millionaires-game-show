#include "scene_manager.hpp"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "game.hpp"
#include "menu.hpp"
#include "game_won.hpp"
#include "game_over.hpp"
#include "text_manager.hpp"

bool SceneManager::PHONE_USED = false;
bool SceneManager::AUDIENCE_USED = false;
bool SceneManager::FIFTY_FIFTY_USED = false;

SDL_Rect Mouse::pointer;
SDL_Renderer* SceneManager::renderer = nullptr;
SDL_Event SceneManager::event;
Mouse* mouse = nullptr;

InputManager SceneManager::inputManager;
ObjectManager SceneManager::objectManager;

SceneManager::~SceneManager(){}
SceneManager::SceneManager(){}

SceneManager& SceneManager::getInstance(){
    static SceneManager INSTANCE;
    return INSTANCE;
}

void SceneManager::init(const char* title, int xpos, int ypos, int width, int height){
    if(SDL_Init(SDL_INIT_EVERYTHING)){
        isRunning = false;
        std::cout << "Game init error" << std::endl;
        exit(1);
    }
    if(IMG_Init(IMG_INIT_PNG) < 0){
        std::cout << "IMG_Init error: " << IMG_GetError() << std::endl;
        isRunning = false;
        exit(1);
    }
    if (TTF_Init() < 0) {
        std::cout << "TTF_Init error: " << TTF_GetError() << std::endl;
        isRunning = false;
        exit(1);
    
    }

    mouse = new Mouse();
    
    window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL){
        std::cout << "Window creation error" << std::endl;
        isRunning = false;
        exit(1);
    }
    TextManager::getInstance().init();
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    isRunning = true;

    Game* game = &Game::getInstance();
    MainMenu* menu = &MainMenu::getInstance();
    GameWon* gameWon = &GameWon::getInstance();
    GameOver* gameOver = &GameOver::getInstance();

    scenes.emplace_back(menu); // the order matters
    scenes.emplace_back(game);
    scenes.emplace_back(gameWon);
    scenes.emplace_back(gameOver);

    for(auto& scene :scenes){
        scene->init();
    }
    currentScene = START_MENU;
    
    scenes[currentScene]->start();
}

void SceneManager::processMessage(std::unique_ptr<BaseMessage> msg){
    MessageType type = msg->getMessageType();
    switch (type){
    case FRONT_START_GAME:
        PHONE_USED = false;
        FIFTY_FIFTY_USED = false;
        AUDIENCE_USED = false;
        changeScene(GAME);
        scenes[GAME]->processMessage(std::move(msg));
        break;
    case FRONT_50_50:
        FIFTY_FIFTY_USED = true;
        scenes[GAME]->processMessage(std::move(msg));
        break;
    case FRONT_PHONE:
        PHONE_USED = true;
        scenes[GAME]->processMessage(std::move(msg));
        break;
    case FRONT_AUDIENCE:
        AUDIENCE_USED = true;
        scenes[GAME]->processMessage(std::move(msg));
        break;
    case FRONT_GAME_WON:
        changeScene(GAME_FINISHED);
        break;
    case FRONT_GAME_OVER:
        changeScene(GAME_OVER);
        break;
    case FRONT_EXIT:
        SceneManager::getInstance().quit();
        break;
    default:
        scenes[currentScene]->processMessage(std::move(msg));
        break;
    }
}

void SceneManager::run(){
    SDL_PollEvent(&event);
    inputManager.update();
    mouse->update();
    Bridge::getInstance().update();
    objectManager.update();
    SDL_RenderClear(renderer);
    objectManager.draw();
    SDL_RenderPresent(renderer);
}

void SceneManager::changeScene(GameScene scene){
    currentScene = scene;
    inputManager.clear();
    objectManager.clear();
    scenes[scene]->start();
}

void SceneManager::quit(){
    isRunning = false;
}

void SceneManager::clear(){
    
    for(auto& scene : scenes){
        scene->clean();
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}

bool SceneManager::running(){
    return isRunning;
}


bool SceneManager::getFiftyFifty(){ return FIFTY_FIFTY_USED; }
bool SceneManager::getPhone(){ return PHONE_USED; }
bool SceneManager::getAudience(){ return AUDIENCE_USED; }