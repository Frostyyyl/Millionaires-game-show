#include "game.hpp"
#include "button_system.hpp"
#include "scene_manager.hpp"

std::vector<TextButton*> answers; // here because i need to access it
TextSprite* question = nullptr;
DoubleTextsprite* currentQuestion = nullptr;
DoubleTextsprite* score = nullptr;

Game::Game(){}
Game::~Game(){}

Game& Game::getInstance(){
    static Game INSTANCE;
    return INSTANCE;
}

void Game::init (){
    question = new TextSprite("images/question_sprite.png", 60, 395, " ");
    currentQuestion = new DoubleTextsprite("images/addons_sprite.png", 80, 365, "Question:", "0", "right");
    score = new DoubleTextsprite("images/addons_sprite.png", 695, 365, "Score:", "0", "right");

    TextButton* A = new TextButton("images/text_button_sprite.png", 60, 525, "A:", " ", 0);
    TextButton* B = new TextButton("images/text_button_sprite.png", 515, 525, "B:",  " ", 1);
    TextButton* C = new TextButton("images/text_button_sprite.png", 60, 605, "C:", " ", 2);
    TextButton* D = new TextButton("images/text_button_sprite.png", 515, 605, "D:", " ", 3);
    answers.emplace_back(A);
    answers.emplace_back(B);
    answers.emplace_back(C);
    answers.emplace_back(D);
}

void Game::start(){
    for (auto & i : answers){
        SceneManager::getInstance().objectManager.addObject(i);
        SceneManager::getInstance().inputManager.addButton(i);  
    }

    SceneManager::getInstance().objectManager.addObject(question);
    SceneManager::getInstance().objectManager.addObject(currentQuestion);
    SceneManager::getInstance().objectManager.addObject(score);
}

void Game::clean(){
}

void Game::processMessage(std::unique_ptr<BaseMessage> msg) {
    std::cout << "here is game got message" << std::endl;
    MessageType type = msg->getMessageType();
    switch (type)
    {
    case FRONT_START_GAME:
    case FRONT_NEXT_QUESTION:
        if (auto questionMsg = dynamic_cast<Message<std::pair<std::string, std::vector<std::string>>, int, std::string>*>(msg.get())) {
            auto arguments = std::get<0>(questionMsg->arguments);
            for(int i = 0; i < 4; i++) {
                answers[i]->loadData(arguments.second[i]);
            }
            question->loadData(arguments.first);
            int counter = std::get<1>(questionMsg->arguments);
            std::string s = std::get<2>(questionMsg->arguments);
            currentQuestion->loadData(std::to_string(counter));
            score->loadData(s);
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