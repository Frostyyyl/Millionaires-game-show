#pragma once
#include <iostream>
#include <memory>
#include "SDL.h"
#include "message.hpp"

class Game{
public:
    ~Game();
    static Game& getInstance();
    
    void init(const char* title, int xpos, int ypos, int width, int height);
    void update();
    void handleEvent();
    void render();
    void clean();
    void quit();
    bool running();

    void processMessage(std::unique_ptr<BaseMessage> msg);

    static SDL_Renderer* renderer;
    static SDL_Event event;
private:
    Game();
    SDL_Window* window;
    bool isRunning;
};