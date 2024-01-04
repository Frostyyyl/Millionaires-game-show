#pragma once
#include <iostream>
#include "SDL.h"

class Game{
public:
    Game();
    ~Game();
    
    void init(const char* title, int xpos, int ypos, int width, int height);
    void update();
    void handleEvent();
    void render();
    void clean();
    void quit();
    bool running();

    static SDL_Renderer* renderer;
    static SDL_Event event;
private:
    SDL_Window* window;
    bool isRunning;
};