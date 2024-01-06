#include <iostream>
#include "SDL.h"
#include "scene_manager.hpp"
#include "questions_handler.hpp"

const int WIDTH = 1000, HEIGHT = 700;
const int FRAMES_PER_SECOND = 60;
const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND;


int main( int argc, char* argv[] ){

    Uint32 frameStart;
    int frameTime;

    // im not sure but i think it needs to stay here cause i got an error with questioncounter while in scenemanager.init()
    QuestionsHandler question("data/database.json");

    SceneManager::getInstance().init("Milionaires", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT);
    
    while(SceneManager::getInstance().running()) {
        frameStart = SDL_GetTicks();
        SceneManager::getInstance().run();

        frameTime = SDL_GetTicks() - frameStart;

        if(FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }
    return 0;
}