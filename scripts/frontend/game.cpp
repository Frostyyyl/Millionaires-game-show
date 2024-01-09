#include "game.hpp"
#include "button_system.hpp"
#include "scene_manager.hpp"

std::vector<TextButton*> answers;
Sprite* background = nullptr;
TextSprite* question = nullptr;
DoubleTextsprite* score = nullptr;
DoubleTextsprite* currentQuestion = nullptr;
DoubleTextsprite* currentPrize = nullptr;
Button* phoneLifeline = nullptr;
Button* audienceLifeline = nullptr;
Button* fiftyFiftyLifeline = nullptr;

Sprite* phoneFriend = nullptr;
TextSprite* phoneQuestion = nullptr;
TextSprite* phoneAnswer = nullptr;
std::vector<TextSprite*> percentages;

Game::Game(){}
Game::~Game(){}

Game& Game::getInstance(){
    static Game INSTANCE;
    return INSTANCE;
}

void Game::init (){
    background = new Sprite("images/background.png", 0, 0);
    question = new TextSprite("images/question_sprite.png", 60, 425, " ");
    score = new DoubleTextsprite("images/score.png", 730, 15, "Score: ", "0", "right");
    currentQuestion = new DoubleTextsprite("images/addons_sprite.png", 80, 395, "Question:", "0", "right");
    currentPrize = new DoubleTextsprite("images/addons_sprite.png", 695, 395, "Prize:", "0", "right");
    phoneLifeline = new Button("images/friend_phone.png", 730, 95, PHONE);
    audienceLifeline = new Button("images/audience.png", 810, 95, AUDIENCE);
    fiftyFiftyLifeline = new Button("images/fifty_fifty.png", 890, 95, FIFTY_FIFTY);

    phoneFriend = new Sprite("images/friend_sprite.png", 60, 15);
    phoneQuestion = new TextSprite("images/phone_question.png", 240, 15, " ");
    phoneAnswer = new TextSprite("images/phone_answer.png", 240, 230, " ");

    TextSprite* percentA = new TextSprite("images/percentage_sprite.png", 60, 15, " ");
    TextSprite* percentB = new TextSprite("images/percentage_sprite.png", 60, 65, " ");
    TextSprite* percentC = new TextSprite("images/percentage_sprite.png", 60, 115, " ");
    TextSprite* percentD = new TextSprite("images/percentage_sprite.png", 60, 165, " ");
    percentages.emplace_back(percentA);
    percentages.emplace_back(percentB);
    percentages.emplace_back(percentC);
    percentages.emplace_back(percentD);

    TextButton* A = new TextButton("images/text_button_sprite.png", 60, 555, "A:", " ", 0);
    TextButton* B = new TextButton("images/text_button_sprite.png", 515, 555, "B:",  " ", 1);
    TextButton* C = new TextButton("images/text_button_sprite.png", 60, 635, "C:", " ", 2);
    TextButton* D = new TextButton("images/text_button_sprite.png", 515, 635, "D:", " ", 3);
    answers.emplace_back(A);
    answers.emplace_back(B);
    answers.emplace_back(C);
    answers.emplace_back(D);
}

void Game::start(){
    SceneManager::getInstance().objectManager.addObject(background);
    
    SceneManager::getInstance().objectManager.addObject(currentQuestion);
    SceneManager::getInstance().objectManager.addObject(currentPrize);

    for (auto & i : answers){
        SceneManager::getInstance().objectManager.addObject(i);
        SceneManager::getInstance().inputManager.addButton(i);  
    }
    if (!SceneManager::getInstance().getFiftyFifty()){ 
        SceneManager::getInstance().objectManager.addObject(fiftyFiftyLifeline);
        SceneManager::getInstance().inputManager.addButton(fiftyFiftyLifeline);
    }
    if (!SceneManager::getInstance().getPhone()){ 
        SceneManager::getInstance().objectManager.addObject(phoneLifeline);
        SceneManager::getInstance().inputManager.addButton(phoneLifeline);
    }
    if (!SceneManager::getInstance().getAudience()){ 
        SceneManager::getInstance().objectManager.addObject(audienceLifeline);
        SceneManager::getInstance().inputManager.addButton(audienceLifeline);
    }
    SceneManager::getInstance().objectManager.addObject(question);
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
    {
    case FRONT_NEXT_QUESTION:
        if (auto questionMsg = dynamic_cast<Message<std::pair<std::string, std::vector<std::string>>, int, std::string, std::string>*>(msg.get())) {
            auto arguments = std::get<0>(questionMsg->arguments);
            for(int i = 0; i < 4; i++) {
                answers[i]->loadData(arguments.second[i]);
            }
            question->loadData(arguments.first);
            ANSWER_SELECTED = false;
            int counter = std::get<1>(questionMsg->arguments);
            std::string prize = std::get<2>(questionMsg->arguments);
            std::string s = std::get<3>(questionMsg->arguments);
            currentQuestion->loadData(std::to_string(counter));
            currentPrize->loadData(prize);
            score->loadData(s);
            SceneManager::getInstance().changeScene(GAME);
        }
        else{
            std::cerr << "Error while reading Question from Message" << std::endl;
        }
        break;
    }
    case FRONT_PHONE:
        for (int i = 0; i < 4; i++){
            SceneManager::getInstance().objectManager.erase(percentages[i]);
        }
        if (auto questionMsg = dynamic_cast<Message<std::vector<std::string>>*>(msg.get())) {
            auto arguments = std::get<0>(questionMsg->arguments);
            phoneQuestion->loadData(arguments[0]);
            phoneAnswer->loadData(arguments[1]);
            SceneManager::getInstance().objectManager.addObject(phoneFriend);
            SceneManager::getInstance().objectManager.addObject(phoneQuestion);
            SceneManager::getInstance().objectManager.addObject(phoneAnswer);  
            SceneManager::getInstance().objectManager.erase(phoneLifeline);  
            SceneManager::getInstance().inputManager.erase(phoneLifeline);  
        }
        else{
            std::cerr << "Error while reading Lifeline from Message" << std::endl;
        }
        break;
    case FRONT_50_50:
        if (auto questionMsg = dynamic_cast<Message<std::vector<std::string>>*>(msg.get())) {
            auto arguments = std::get<0>(questionMsg->arguments);
            answers[0]->loadData(arguments[0]);
            answers[1]->loadData(arguments[1]);
            SceneManager::getInstance().objectManager.erase(answers[2]);  
            SceneManager::getInstance().inputManager.erase(answers[2]);  
            SceneManager::getInstance().objectManager.erase(answers[3]);  
            SceneManager::getInstance().inputManager.erase(answers[3]); 
            SceneManager::getInstance().objectManager.erase(fiftyFiftyLifeline);  
            SceneManager::getInstance().inputManager.erase(fiftyFiftyLifeline);  
        }
        else{
            std::cerr << "Error while reading Lifeline from Message" << std::endl;
        }
        break;
    case FRONT_AUDIENCE:
        SceneManager::getInstance().objectManager.erase(phoneFriend);
        SceneManager::getInstance().objectManager.erase(phoneQuestion);
        SceneManager::getInstance().objectManager.erase(phoneAnswer); 
        if (auto questionMsg = dynamic_cast<Message<std::vector<std::string>>*>(msg.get())) {
            auto arguments = std::get<0>(questionMsg->arguments);
            for (int i = 0; i < arguments.size(); i++){
                percentages[i]->loadData(arguments[i]);
                SceneManager::getInstance().objectManager.addObject(percentages[i]);
            }
            SceneManager::getInstance().objectManager.erase(audienceLifeline);  
            SceneManager::getInstance().inputManager.erase(audienceLifeline);  
        }
        else{
            std::cerr << "Error while reading Lifeline from Message" << std::endl;
        }
        break;
    default:
        std::cerr << "Frontend could not process a message" << std::endl;
        break;
    }
}