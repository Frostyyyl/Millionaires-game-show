#include <iostream>
#include "SDL.h"
#include "game.hpp"
#include "questions_handler.hpp"

const int WIDTH = 1000, HEIGHT = 700;
const int FRAMES_PER_SECOND = 60;
const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND;


int main( int argc, char* argv[] ){

    Uint32 frameStart;
    int frameTime;
    QuestionsHandler question("data/database.json");

    Game::getInstance().init("Milionaires", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT);
    
    while(Game::getInstance().running()) {
        frameStart = SDL_GetTicks();
        
        Game::getInstance().handleEvent();
        Game::getInstance().update();
        Game::getInstance().render();

        frameTime = SDL_GetTicks() - frameStart;

        if(FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
    Game::getInstance().clean();
    return 0;
}