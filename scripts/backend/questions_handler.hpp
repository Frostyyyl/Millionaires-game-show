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

extern unsigned seed;
extern std::mt19937 g;
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
    static QuestionsHandler& getInstance();
    bool checkAnswer(int index);
    void resetQuestions();
    Question getQuestion();
    std::pair<std::string, std::vector<std::string>> getNextQuestion();
    void setAvailableAnswers(std::vector<std::string> answers);
    std::vector<std::string> getAvailableAnswers();
    int getTier();
    int getQuestionCounter();
    std::string getScore();
    void processMessage(std::unique_ptr<BaseMessage> msg);
};