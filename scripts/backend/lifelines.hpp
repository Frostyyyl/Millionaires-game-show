#pragma once
#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include "questions_handler.hpp"

class Lifeline{
protected:
    QuestionsHandler questionsHandler;
public:
    Lifeline();
    ~Lifeline();
    virtual std::vector<std::string> interact() {return std::vector<std::string>();};
};

class Half:public Lifeline{
public:
    std::vector<std::string> interact() override;   //returns vector of viable options
};

class Phone:public Lifeline{
private:
    int setKnowledge();
    int chooseAnswer(bool returnCorrectAnswer);
    std::string generatePrompt();
    std::string generateAnswer(int chosenAnswer, int knowledge);
public:
    std::vector<std::string> interact() override; //returns two messages
}; 

class Audience:public Lifeline{
private:
    int setCorrectPercentage();
    std::vector<int> getIncorrectPercentages(int correctPercentage);
    std::vector<std::string> generateMessage(int correctPercentage, std::vector<int> incorrectPercentages);
public:
    std::vector<std::string> interact() override; //return vector of strings like "A: xx%"
};