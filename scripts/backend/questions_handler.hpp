#pragma once

#include <chrono>
#include <random>
#include <string>
#include <utility>
#include <vector>
#include "questions_loader.hpp"

class QuestionsHandler{
private:
    static QuestionsHandler *Instance;
    std::vector<std::vector<Question>> questions;
    std::vector<std::vector<Question>> availableQuestions;
    Question currentQuestion;
    int tier;
    std::vector<std::string> availableAnswers;
    void drawQuestion();
public:
    QuestionsHandler(const std::string filename);
	~QuestionsHandler();
    static QuestionsHandler getInstance();
    bool checkAnswer(std::string chosenAnswer);
    void resetQuestions();
    Question getQuestion();
    std::pair<std::string, std::vector<std::string>> getNextQuestion(int tier);
    void setAvailableAnswers(std::vector<std::string> answers);
    std::vector<std::string> getAvailableAnswers();
    int getTier();
};

class Lifeline{
protected:
    QuestionsHandler questionsHandler;
public:
    Lifeline();
    ~Lifeline();
    virtual std::vector<std::string> interact();
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