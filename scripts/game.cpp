#include "game.hpp"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "object_system.hpp"
#include "sprite_system.hpp"
#include "input_manager.hpp"
#include "button_object.hpp"

SDL_Rect Mouse::pointer;
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
    if (TTF_Init() < 0) {
        std::cout << "TTF_Init error: " << TTF_GetError() << std::endl;
        isRunning = false;
        exit(1);
    }

    window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL){
        std::cout << "Window creation error" << std::endl;
        isRunning = false;
        exit(1);
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    isRunning = true;

    // here is creating and adding objects to ObjectManager and InputManager
    // will probably need to change this later so it's more clear
    
    Mouse* mouse = new Mouse();

    Button* button = new Button("images/button_spritesheet.png", 700, 40, 2, 1);
    TextButton* button_A = new TextButton("images/text_button_sprite.png", 60, 425, "fonts/mont-heavy.otf", "Hungary", 84, 2, 1);
    TextButton* button_B = new TextButton("images/text_button_sprite.png", 515, 425, 
            "fonts/mont-heavy.otf", "What is the capital of France?", 40, 2, 1);
    TextButton* button_C = new TextButton("images/text_button_sprite.png", 60, 555, "fonts/mont-heavy.otf", "Pekin", 72, 2, 1);
    TextButton* button_D = new TextButton("images/text_button_sprite.png", 515, 555, "fonts/mont-heavy.otf", "Madrit", 72, 2, 1);
    TextSprite* question = new TextSprite("images/question_sprite.png", 60, 295, 
            "fonts/mont-heavy.otf", "What is the capital of France? What is mars, earth or even the sun? ", 40, 1, 1);

    objectManager.addObject(mouse);
    objectManager.addObject(button);
    objectManager.addObject(button_A);
    objectManager.addObject(button_B);
    objectManager.addObject(button_C);
    objectManager.addObject(button_D);
    objectManager.addObject(question);
    inputManager.addButton(button);
    inputManager.addButton(button_A);
    inputManager.addButton(button_B);
    inputManager.addButton(button_C);
    inputManager.addButton(button_D);
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
    TTF_Quit();
    IMG_Quit();
}

//for now not used, want to add this to inputManager
void Game::quit(){
    isRunning = false;
}

bool Game::running(){
    return isRunning;
}