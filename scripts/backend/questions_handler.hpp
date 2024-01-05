#pragma once

#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <fstream>
#include <vector>
#include <memory>
#include "json.hpp"
#include "message.hpp"

using json = nlohmann::json;
struct Question {
    std::string question;
    std::string correctAnswer;
    std::string incorrectAnswers[3];
};

/*
    loadJSON returns all questions:
    easy questions - questions[0]
    medium questions - questions[1]
    hard questions - questions[2]
*/
std::vector<std::vector<struct Question>> loadJSON(const std::string filename);

class QuestionsHandler{
private:
    static QuestionsHandler *Instance;
    std::vector<std::vector<Question>> questions;
    std::vector<std::vector<Question>> availableQuestions;
    Question currentQuestion;
    int questionCounter;
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
    std::pair<std::string, std::vector<std::string>> getNextQuestion();
    void setAvailableAnswers(std::vector<std::string> answers);
    std::vector<std::string> getAvailableAnswers();
    int getTier();
    int getQuestionCounter();
    void processMessage(std::unique_ptr<BaseMessage> msg);
};

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