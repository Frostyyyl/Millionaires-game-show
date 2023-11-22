#include <iostream>
#include "SDL.h"
#include "game.hpp"

const int WIDTH = 800, HEIGHT = 600;
const int FRAMES_PER_SECOND = 60;
const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND;


Game *game = nullptr;

int main( int argc, char* argv[] ){

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Milionaires", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT);
    
    while(game->running()) {
        frameStart = SDL_GetTicks();
        
        game->handleEvent();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
    game->clean();
    return 0;
}