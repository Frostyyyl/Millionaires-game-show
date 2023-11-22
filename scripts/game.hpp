#pragma once

#include "SDL.h"
#include <iostream>

class Game{
public:
    Game();
    ~Game();
    
    void init(const char* title, int xpos, int ypos, int width, int height);
    void update();
    void handleEvent();
    void render();
    void clean();
    bool running();

    static SDL_Renderer* renderer;
private:
    SDL_Window* window;
    bool isRunning;
};