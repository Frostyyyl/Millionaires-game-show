#pragma once

#include <vector>
#include "SDL.h"
#include <memory>
#include "scene.hpp"
#include "input_manager.hpp"

enum GameScene{
    START_MENU, // menu
    GAME, // questions etc
    GAME_FINISHED, // gamecompleted - youre a milionaire
    GAME_OVER, // game over
};

class SceneManager
{
private:
    static bool PHONE_USED;
    static bool AUDIENCE_USED;
    static bool FIFTY_FIFTY_USED;
public:
    static SceneManager& getInstance();
    void init(const char* title, int xpos, int ypos, int width, int height);
    void run();
    void changeScene(GameScene scene);
    void quit();
    void clear();
    bool running();

    void processMessage(std::unique_ptr<BaseMessage> msg);

    ~SceneManager();
    
    static SDL_Renderer* renderer;
    static SDL_Event event;
    static InputManager inputManager;
    static ObjectManager objectManager;
    GameScene currentScene;

    static bool getFiftyFifty();
    static bool getPhone();
    static bool getAudience();
private:
    std::vector<Scene*> scenes;
    SDL_Window* window;
    bool isRunning;
    SceneManager();  
};
