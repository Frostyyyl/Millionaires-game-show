#include "lifelines.hpp"
#include "bridge.hpp"

Lifeline::Lifeline(){}

Lifeline::~Lifeline(){}

Half& Half::getInstance(){
    static Half INSTANCE;
    return INSTANCE;
}

std::vector<std::string> Half::interact(){
    Question question = QuestionsHandler::getInstance().getQuestion();
    std::cout << question.correctAnswer << std::endl;
    std::vector<std::string> answers;
    answers.push_back(question.correctAnswer);
    std::uniform_int_distribution<int> rng(0, 2);
    answers.push_back(question.incorrectAnswers[rng(g)]);
    std::shuffle(answers.begin(), answers.end(), g);
    QuestionsHandler::getInstance().setAvailableAnswers(answers);
    return answers;
}

Phone& Phone::getInstance(){
    static Phone INSTANCE;
    return INSTANCE;
}

int Phone::setKnowledge(){
    int tier = QuestionsHandler::getInstance().getTier();
    if (tier == 0){
        std::uniform_int_distribution<int> rng(80,99);
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
    Question question = QuestionsHandler::getInstance().getQuestion();
    std::vector<std::string> availableAnswers = QuestionsHandler::getInstance().getAvailableAnswers();
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
    Question question = QuestionsHandler::getInstance().getQuestion();
    std::string beggining = "Hello there. General Kenobi...\nMmm, anyway we are calling from the \"Millionaires\", because we need Your help. You have 30 seconds to answer this question.";
    return beggining;
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
        returnCorrectAnswer = true;
    } else {
        returnCorrectAnswer = false;
    }
    std::cout << knowledge << '\n';
    std::cout << returnCorrectAnswer << '\n';
    int chosenAnswer = this->chooseAnswer(returnCorrectAnswer);
    std::string prompt = generatePrompt();
    std::string answer = generateAnswer(chosenAnswer, knowledge);
    std::vector<std::string> message = {prompt, answer};
    return message;
}

Audience& Audience::getInstance(){
    static Audience INSTANCE;
    return INSTANCE;
}

int Audience::setCorrectPercentage(){
    int tier = QuestionsHandler::getInstance().getTier();
    std::vector<std::string> availableAnswers = QuestionsHandler::getInstance().getAvailableAnswers();
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
    std::vector<std::string> availableAnswers = QuestionsHandler::getInstance().getAvailableAnswers();
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
    std::vector<std::string> message, availableAnswers = QuestionsHandler::getInstance().getAvailableAnswers();
    Question question = QuestionsHandler::getInstance().getQuestion();
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

void Half::processMessage(std::unique_ptr<BaseMessage> msg){
    std::vector<std::string> res = interact();
    Bridge::getInstance().addMessage(FRONT_50_50, res);
}

void Phone::processMessage(std::unique_ptr<BaseMessage> msg){
    std::vector<std::string> res = interact();
    Bridge::getInstance().addMessage(FRONT_PHONE, res);
}

void Audience::processMessage(std::unique_ptr<BaseMessage> msg){
    std::vector<std::string> res = interact();
    Bridge::getInstance().addMessage(FRONT_AUDIENCE, res);
}