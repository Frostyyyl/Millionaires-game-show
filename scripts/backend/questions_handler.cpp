#include "questions_handler.hpp"
#include "bridge.hpp"

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 g(seed);

QuestionsHandler* QuestionsHandler::Instance = nullptr;

std::vector<std::vector<struct Question>> loadJSON(const std::string filename){
    std::vector<std::vector<struct Question>> questions(3);
    std::ifstream jsonFile(filename);
    if(jsonFile.is_open()){
        json j = json::parse(jsonFile);
        for (int i = 0; i < j["easy"].size(); i++){
            Question q = {.question = j["easy"][i]["question"], .correctAnswer = j["easy"][i]["correct_answer"], .incorrectAnswers = {j["easy"][i]["incorrect_answers"][0], j["easy"][i]["incorrect_answers"][1], j["easy"][i]["incorrect_answers"][2]}};
            questions[0].push_back(q);
        }
        for (int i = 0; i < j["medium"].size(); i++){
            Question q = {.question = j["medium"][i]["question"], .correctAnswer = j["medium"][i]["correct_answer"], .incorrectAnswers = {j["medium"][i]["incorrect_answers"][0], j["medium"][i]["incorrect_answers"][1], j["medium"][i]["incorrect_answers"][2]}};
            questions[1].push_back(q);
        }
        for (int i = 0; i < j["hard"].size(); i++){
            Question q = {.question = j["hard"][i]["question"], .correctAnswer = j["hard"][i]["correct_answer"], .incorrectAnswers = {j["hard"][i]["incorrect_answers"][0], j["hard"][i]["incorrect_answers"][1], j["hard"][i]["incorrect_answers"][2]}};
            questions[2].push_back(q);
        }
        return questions;
    }else{
        std::cerr << "Error. Couldn't open file: " << filename << std::endl;
        return questions;
    }
}

QuestionsHandler::QuestionsHandler(const std::string filename){
    if (Instance!=nullptr){
        std::cerr << "ERROR: Questions Handler already exists!" << std::endl;
        exit(1);
    }
    Instance = this;
    questions = loadJSON(filename);
    resetQuestions();
}

QuestionsHandler::~QuestionsHandler(){}

void QuestionsHandler::drawQuestion(){
    std::uniform_int_distribution<int> rng(0, availableQuestions[tier].size()-1);
    int questionIndex = rng(g);
    currentQuestion = availableQuestions[tier][questionIndex];
    availableQuestions[tier].erase(availableQuestions[tier].begin() + questionIndex);
}

QuestionsHandler& QuestionsHandler::getInstance(){
    return *Instance;
}

bool QuestionsHandler::checkAnswer(int index){
    if (availableAnswers[index] == currentQuestion.correctAnswer){
        return true;
    }
    else {
        return false;
    }
}

void QuestionsHandler::resetQuestions(){
    availableQuestions = questions;
    questionCounter = 0;
    tier = 0;
}

Question QuestionsHandler::getQuestion(){
    return currentQuestion;
}

std::pair<std::string, std::vector<std::string>> QuestionsHandler::getNextQuestion(){
    questionCounter++;
    if (questionCounter >= 1 && questionCounter <= 4){
        tier = 0;
    } else if (questionCounter <= 8){
        tier = 1;
    } else if (questionCounter <= 10){
        tier = 2;
    } else {
        std::cerr << "ERROR: Game has been already won" << std::endl;
        exit(1);
    }
    this->drawQuestion();
    std::string questionText = currentQuestion.question;
    std::vector<std::string> answers;
    answers.push_back(currentQuestion.correctAnswer);
    for (int i = 0; i < 3; i++){
        answers.push_back(currentQuestion.incorrectAnswers[i]);
    }
    std::shuffle(answers.begin(), answers.end(), g);
    availableAnswers = answers;
    std::pair<std::string, std::vector<std::string>> questionPair = std::make_pair(questionText, answers);
    return questionPair;
}

void QuestionsHandler::setAvailableAnswers(std::vector<std::string> answers){
    availableAnswers = answers;
}

std::vector<std::string> QuestionsHandler::getAvailableAnswers(){
    return availableAnswers;
}

int QuestionsHandler::getTier(){
    return tier;
}

int QuestionsHandler::getQuestionCounter(){
    return questionCounter;
}

std::string QuestionsHandler::getScore(){ // goofy but enough
    switch (questionCounter){
    case 1:
        return "0";
    case 2:
        return "1000";
    case 3:
        return "5000";
    case 4:
        return "10 000";
    case 5:
        return "20 000";
    case 6:
        return "40 000";
    case 7:
        return "75 000";
    case 8:
        return "125 000";
    case 9:
        return "250 000";
    case 10:
        return "500 000";
    default:
        break;
    }
    return " ";
}

std::string QuestionsHandler::getPrize(){ // goofy but enough
    switch (questionCounter){
    case 1:
        return "1000";
    case 2:
        return "4000";
    case 3:
        return "5000";
    case 4:
        return "10 000";
    case 5:
        return "20 000";
    case 6:
        return "35 000";
    case 7:
        return "50 000";
    case 8:
        return "125 000";
    case 9:
        return "250 000";
    case 10:
        return "500 000";
    default:
        break;
    }
    return " ";
}

#include <iostream>

void QuestionsHandler::processMessage(std::unique_ptr<BaseMessage> msg) {
    MessageType type = msg->getMessageType();
    switch (type)
    {{
    case BACK_START_GAME:
        resetQuestions(); // added this so i could use start button as reset button
        std::pair<std::string, std::vector<std::string>> res = getNextQuestion();
        Bridge::getInstance().addMessage(FRONT_START_GAME, res, questionCounter, getPrize(), getScore()); 
        break; 
    }{
    case BACK_ANSWER:
        if (auto answerMsg = dynamic_cast<Message<int>*>(msg.get())) {
            int ans = std::get<0>(answerMsg->arguments);
            if(checkAnswer(ans)){
                if(questionCounter == 10){ // if game completed
                    Bridge::getInstance().addMessage(FRONT_GAME_WON);
                }
                else{
                    std::pair<std::string, std::vector<std::string>> res = getNextQuestion();
                    Bridge::getInstance().addMessage(FRONT_NEXT_QUESTION, res, questionCounter, getPrize(), getScore()); // need to add here , questioncounter
                }
            }
            else{
                Bridge::getInstance().addMessage(FRONT_GAME_OVER);
            }
        } else {
            std::cerr << "Error while reading Answer from Message" << std::endl;
        }
        break;
    }
    default:
        std::cerr << "Backend could not process a message" << std::endl;
        break;
    }
}