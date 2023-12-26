#include "game.hpp"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "object_system.hpp"
#include "sprite_object.hpp"
#include "input_manager.hpp"
#include "button_object.hpp"
//#include "text_sprite.hpp"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

ObjectManager objectManager;
InputManager inputManager; //wanted to make it static but failed ;/

Game::Game(){}

Game::~Game(){}

void Game::init(const char* title, int xpos, int ypos, int width, int height){
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
    std::cout << TTF_GetError() << std::endl;
    //this part crashes whole program idk why
    // if (TTF_Init() < 0) {
    //     std::cout << "TTF_Init error" << std::endl;
    //     // Handle initialization failure
    //     isRunning = false;
    //     exit(1);
    // } else {
    //     std::cout << "TTF_Init successful!" << std::endl;
    // }

    window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL){
        std::cout << "Window creation error" << std::endl;
        exit(1);
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    isRunning = true;

    // here is creating and adding objects to ObjectManager and InputManager
    // will probably need to change this later so it's more clear
    
    Button* button = new Button("images/button_spritesheet.png", 100, 300, 2, 1);
    //TextSprite* text = new TextSprite("images/button_spritesheet.png", 100, 20, "a.ttf", "lol", 1, 1);
    objectManager.addObject(button);
    //objectManager.addObject(text);
    inputManager.addButton(button);
}

void Game::update(){
    //game update 
    objectManager.update();
}

void Game::handleEvent(){
    SDL_PollEvent(&event);
    inputManager.update();
    switch (event.type) //for now unfortunately I had to have quitting here
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
    //TTF_Quit();
    //IMG_Quit();
}

//for now not used, want to add this to inputManager
void Game::quit(){
    isRunning = false;
}

bool Game::running(){
    return isRunning;
}