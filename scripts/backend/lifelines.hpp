#pragma once
#include <vector>
#include <string>
#include <chrono>
#include <iostream>
#include "questions_handler.hpp"

class Lifeline{
protected:
    QuestionsHandler* questionsHandler;
public:
    Lifeline();
    ~Lifeline();
    virtual std::vector<std::string> interact() {return std::vector<std::string>();};
    virtual void processMessage(std::unique_ptr<BaseMessage> msg) = 0;
};

class Half:public Lifeline{
public:
    static Half& getInstance();
    std::vector<std::string> interact() override;   //returns vector of viable options
    void processMessage(std::unique_ptr<BaseMessage> msg) override;
};

class Phone:public Lifeline{
private:
    int setKnowledge();
    int chooseAnswer(bool returnCorrectAnswer);
    std::string generatePrompt();
    std::string generateAnswer(int chosenAnswer, int knowledge);
public:
    static Phone& getInstance();
    std::vector<std::string> interact() override; //returns two messages
    void processMessage(std::unique_ptr<BaseMessage> msg) override;
}; 

class Audience:public Lifeline{
private:
    int setCorrectPercentage();
    std::vector<int> getIncorrectPercentages(int correctPercentage);
    std::vector<std::string> generateMessage(int correctPercentage, std::vector<int> incorrectPercentages);
public:
    static Audience& getInstance();
    std::vector<std::string> interact() override; //return vector of strings like "A: xx%"
    void processMessage(std::unique_ptr<BaseMessage> msg) override;
};