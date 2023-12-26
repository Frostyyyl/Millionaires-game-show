#pragma once

#include <chrono>
#include <random>
#include <string>
#include <utility>
#include <vector>
#include "questions_loader.hpp"

class QuestionsHandler{
private:
    std::vector<std::vector<struct Question>> questions;
    std::vector<std::vector<struct Question>> availableQuestions;
public:
    QuestionsHandler(const std::string filename);
	~QuestionsHandler();
    bool checkAnswer(Question question, std::string chosenAnswer);
    void resetQuestions();
    struct Question drawQuestion(int tier);
    std::pair<std::string, std::vector<std::string>> getQuestion(struct Question question);
};