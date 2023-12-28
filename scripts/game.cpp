#include "game.hpp"
#include "object_system.hpp"
#include "sprite_object.hpp"


SDL_Renderer* Game::renderer = nullptr;
ObjectManager objectManager;

Game::Game(){}

Game::~Game(){}

void Game::init(const char* title, int xpos, int ypos, int width, int height){
    if(SDL_Init(SDL_INIT_EVERYTHING)){
        isRunning = false;
        std::cout << "Game init error" << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL){
        std::cout << "Window creation error" << std::endl;
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    isRunning = true;

    // here is creating and adding objects to ObjectManager
    Spritesheet* sprite = new Spritesheet("images/button_spritesheet.png", 100, 20, 2, 1);
    // Sprite* sprite = new Sprite("images/dino.jpg", 220, 0);
    objectManager.addObject(sprite);
}

void Game::update(){
    //game update 
    objectManager.update();
}

void Game::handleEvent(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    
    default:
        break;
    }
}

void Game::render(){
    SDL_RenderClear(renderer);
    //drawing everything here
    objectManager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Game::running(){
    return isRunning;
}