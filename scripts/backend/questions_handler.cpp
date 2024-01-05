#include <questions_handler.hpp>
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
        std::cout << "Error. Couldn't open file: " << filename << std::endl;
        return questions;
    }
}

QuestionsHandler::QuestionsHandler(const std::string filename){
    if (Instance!=nullptr){
        std::cout << "ERROR: Questions Handler already exists!" << std::endl;
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

QuestionsHandler QuestionsHandler::getInstance(){
    return *Instance;
}

bool QuestionsHandler::checkAnswer(std::string chosenAnswer){
    if (chosenAnswer == currentQuestion.correctAnswer){
        return true;
    }
    else {
        return false;
    }
}

void QuestionsHandler::resetQuestions(){
    availableQuestions = questions;
}

Question QuestionsHandler::getQuestion(){
    return currentQuestion;
}

std::pair<std::string, std::vector<std::string>> QuestionsHandler::getNextQuestion(int tier){
    this->tier = tier;
    this->drawQuestion();
    std::string questionText = currentQuestion.question;
    std::vector<std::string> answers;
    answers.push_back(currentQuestion.correctAnswer);
    for (int i = 0; i < 3; i++){
        answers.push_back(currentQuestion.incorrectAnswers[i]);
    }
    std::shuffle(answers.begin(), answers.end(), g);
    availableAnswers = answers;
    std::pair<std::string, std::vector<std::string>> res = std::make_pair(questionText, answers);
    return res;
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

void QuestionsHandler::processMessage(std::unique_ptr<BaseMessage> msg) {
    std::cout << "here is backend got message" << std::endl;
    MessageType type = msg->getMessageType();
    if(type == BACK_START_GAME){ // i will change it to switch statement
        // for now next question cause we dont have startr menu
        std::cout << "lol" << std::endl;
        std::pair<std::string, std::vector<std::string>> res = getNextQuestion(0);
        std::cout << res.first << std::endl;
        Bridge::getInstance().addMessage(FRONT_NEXT_QUESTION, res); 
    }
}

//May or may not work (It's weird)
Lifeline::Lifeline() : questionsHandler(QuestionsHandler::getInstance()){}

Lifeline::~Lifeline() {}

std::vector<std::string> Half::interact(){
    Question question = questionsHandler.getQuestion();
    std::vector<std::string> answers;
    answers.push_back(question.correctAnswer);
    std::uniform_int_distribution<int> rng(0, 3);
    answers.push_back(question.incorrectAnswers[rng(g)]);
    std::shuffle(answers.begin(), answers.end(), g);
    questionsHandler.setAvailableAnswers(answers);
    return answers;
}

int Phone::setKnowledge(){
    int tier = questionsHandler.getTier();
    if (tier == 0){
        std::uniform_int_distribution<int> rng(75,99);
        return rng(g);
    } else if (tier == 1){
        std::uniform_int_distribution<int> rng(55,85);
        return rng(g);
    } else if (tier == 2){
        std::uniform_int_distribution<int> rng(35,75);
        return rng(g);
    } else {
        std::cout << "ERROR: Something wrong with tier" << std::endl;
        exit(1);
    }
}

int Phone::chooseAnswer(bool returnCorrectAnswer){
    Question question = questionsHandler.getQuestion();
    std::vector<std::string> availableAnswers = questionsHandler.getAvailableAnswers();
    if (returnCorrectAnswer){
        auto it = std::find(availableAnswers.begin(), availableAnswers.end(), question.correctAnswer);
        if (it != availableAnswers.end()){
            return std::distance(availableAnswers.begin(), it);
        } else {
            std::cout << "ERROR: Cannot find correct answer in answers" << std::endl;
            exit(1);
        }
    } else {
        std::vector<int> wrongAnswersIndexes;
        for (int i = 0; i < availableAnswers.size(); i++){
            if (availableAnswers[i] != question.correctAnswer){
                wrongAnswersIndexes.push_back(i);
            }
        }
        std::shuffle(wrongAnswersIndexes.begin(), wrongAnswersIndexes.end(), g);
        return wrongAnswersIndexes[0];
    }
}

std::string Phone::generatePrompt(){
    Question question = questionsHandler.getQuestion();
    std::string beggining = "Hello there. We are calling from the game show, because we need Your help. You have 30 seconds to answers this question:\n";
    std::string questionText = question.question;
    return beggining + questionText + "\n";
}

std::string Phone::generateAnswer(int chosenAnswer, int knowledge){
    std::string beggining, answer;
    if (knowledge >= 95){
        beggining = "I know for a fact it is ";
    } else if (knowledge >= 85){
        beggining = "I know it. The answer is ";
    } else if (knowledge >= 70){
        beggining = "I see... It's probably ";
    } else if (knowledge >= 55){
        beggining = "Hmmm... I think it's ";
    } else if (knowledge >= 45){
        beggining = "I don't know, but I would pick ";
    } else if (knowledge >= 35){
        beggining = "I have no idea... I can't help You with that.\n";
        return beggining;
    } else {
        std::cout << "ERROR: Something wrong with knowledge value" << std::endl;
        exit(1);
    }
    if (chosenAnswer == 0){
        answer = "A\n";
    } else if (chosenAnswer == 1){
        answer = "B\n";
    } else if (chosenAnswer == 2){
        answer = "C\n";
    } else if (chosenAnswer == 3){
        answer = "D\n";
    } else {
        std::cout << "ERROR: Something wrong with chosen Answer value" << std::endl;
        exit(1);
    }
    return beggining + answer;
}

std::vector<std::string> Phone::interact(){
    bool returnCorrectAnswer;
    int knowledge = this->setKnowledge();
    std::uniform_int_distribution<int> rng(0,100);
    if (rng(g) <= knowledge){
        returnCorrectAnswer == true;
    } else {
        returnCorrectAnswer == false;
    }
    int chosenAnswer = this->chooseAnswer(returnCorrectAnswer);
    std::string prompt = generatePrompt();
    std::string answer = generateAnswer(chosenAnswer, knowledge);
    std::vector<std::string> message = {prompt, answer};
    return message;
}

int Audience::setCorrectPercentage(){
    int tier = questionsHandler.getTier();
    std::vector<std::string> availableAnswers = questionsHandler.getAvailableAnswers();
    bool halved;
    if (availableAnswers.size() == 2){
        halved = true;
    } else if (availableAnswers.size() == 4){
        halved = false;
    } else{
        std::cout << "ERROR: Something wrong with available answers size" << std::endl;
        exit(1);
    }
    if (tier == 0){
        if (halved){
            std::uniform_int_distribution<int> rng(65,95);
            return rng(g);
        } else {
            std::uniform_int_distribution<int> rng(60,90);
            return rng(g);
        }
    } else if (tier == 1){
        if (halved){
            std::uniform_int_distribution<int> rng(45,80);
            return rng(g);
        } else{
            std::uniform_int_distribution<int> rng(40,75);
            return rng(g);
        }
    } else if (tier == 2){
        if (halved){
            std::uniform_int_distribution<int> rng(25,55);
            return rng(g);
        } else{
            std::uniform_int_distribution<int> rng(10,40);
            return rng(g);
        }
    } else {
        std::cout << "ERROR: Something wrong with tier" << std::endl;
        exit(1);
    }
}

std::vector<int> Audience::getIncorrectPercentages(int correctPercentage){
    std::vector<int> incorrectPercentages;
    std::vector<std::string> availableAnswers = questionsHandler.getAvailableAnswers();
    int leftPercentage = 100 - correctPercentage;
    if (availableAnswers.size() == 2){
        incorrectPercentages.push_back(leftPercentage);
    } else if (availableAnswers.size() == 4){
        for (int i = 0; i < 2; i++){
            std::uniform_int_distribution<int> rng(0,leftPercentage);
            int currentPercentage = rng(g);
            incorrectPercentages.push_back(currentPercentage);
            leftPercentage -= currentPercentage;
        }
        incorrectPercentages.push_back(leftPercentage);
    } else{
        std::cout << "ERROR: Something wrong with available answers size" << std::endl;
        exit(1);
    }
    return incorrectPercentages;
}

std::vector<std::string> Audience::generateMessage(int correctPercentage, std::vector<int> incorrectPercentages){
    std::vector<std::string> message, availableAnswers = questionsHandler.getAvailableAnswers();
    Question question = questionsHandler.getQuestion();
    std::string beggining, percentage;
    int incorrectIndex = 0;
    for (int i = 0; i < availableAnswers.size(); i++){
        if (i == 0){
            beggining = "A: ";
        } else if (i == 1){
            beggining = "B: ";
        } else if (i == 2){
            beggining = "C: ";
        } else if (i == 3){
            beggining = "D: ";
        } else {
            std::cout << "ERROR: something wrong with available answers size" << std::endl;
            exit(1);
        }
        if (availableAnswers[i] == question.correctAnswer){
            percentage = std::to_string(correctPercentage) + "%\n";
        } else{
            percentage = std::to_string(incorrectPercentages[incorrectIndex++]) + "%\n";
        }
        message.push_back(beggining + percentage);
    }
    return message;
}

std::vector<std::string> Audience::interact(){
    int correctPercentage = this->setCorrectPercentage();
    std::vector<int> incorrectPercentages = this->getIncorrectPercentages(correctPercentage);
    return generateMessage(correctPercentage, incorrectPercentages);
}