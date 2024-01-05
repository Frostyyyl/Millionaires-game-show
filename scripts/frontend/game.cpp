#include "game.hpp"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "object_system.hpp"
#include "text_manager.hpp"
#include "sprite_system.hpp"
#include "input_manager.hpp"
#include "button_object.hpp"

SDL_Rect Mouse::pointer;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
ObjectManager objectManager;
InputManager inputManager;

std::vector<TextButton*> answers; // here because i need to access it
QuestionSprite* question = nullptr;

Game::Game(){}
Game::~Game(){}

Game& Game::getInstance(){
    static Game INSTANCE;
    return INSTANCE;
}

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
    textManager.init();

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
    
    Mouse* mouse = new Mouse();     // 🐁 sorry I ate the cheeeeese
    objectManager.addObject(mouse);

    Button* button = new Button("images/button_spritesheet.png", 700, 40, 2, 1);
    question = new QuestionSprite("images/question_sprite.png", 60, 395, "What is the capital of France?");

    TextButton* A = new TextButton("images/text_button_sprite.png", 60, 525, "Hungary", "A", 0);
    TextButton* B = new TextButton("images/text_button_sprite.png", 515, 525, "Francja nie istnieje - poprawna odpowiedz", "B", 1);
    TextButton* C = new TextButton("images/text_button_sprite.png", 60, 605, "Pekin", "C", 2);
    TextButton* D = new TextButton("images/text_button_sprite.png", 515, 605, "Madrid", "D", 3);
    answers.emplace_back(A);
    answers.emplace_back(B);
    answers.emplace_back(C);
    answers.emplace_back(D);

    for (auto & i : answers){
        objectManager.addObject(i);
        inputManager.addButton(i);  
    }

    objectManager.addObject(question);
    objectManager.addObject(button);
    inputManager.addButton(button);
}

void Game::update(){
    //game update 
    Bridge::getInstance().update();
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

void Game::processMessage(std::unique_ptr<BaseMessage> msg) {
    std::cout << "here is frontend got message" << std::endl;
    MessageType type = msg->getMessageType();
    switch (type)
    {
    case FRONT_NEXT_QUESTION:
        if (auto questionMsg = dynamic_cast<Message<std::pair<std::string, std::vector<std::string>>>*>(msg.get())) {
            auto arguments = std::get<0>(questionMsg->arguments);
            for(int i = 0; i < 4; i++) {
                answers[i]->loadAnswer(arguments.second[i]);
            }
            question->loadQuestion(arguments.first);
        }
        else{
            std::cerr << "Error while reading Question from Message" << std::endl;
        }
        ANSWER_SELECTED = false;
        break;
    case FRONT_GAME_OVER:
        std::cout << "wrong answer mate" << std::endl;
        break;
    default:
        break;
    }
}