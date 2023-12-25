#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;

struct Question {
    std::string question;
    std::string correctAnswer;
    std::string incorrectAnswers[3];
    std::string tier;
};

std::vector<struct Question> loadJSON(const std::string filename){
    std::vector<struct Question> questions;
    std::ifstream jsonFile(filename);
    if(jsonFile.is_open()){
        json j = json::parse(jsonFile);
        for (int i = 0; i < j.size(); i++){
            Question q = {.question = j[i]["question"], .correctAnswer = j[i]["correct_answer"], .incorrectAnswers = {j[i]["incorrect_answers"][0], j[i]["incorrect_answers"][1], j[i]["incorrect_answers"][2]}, .tier = j[i]["tier"]};
            questions.push_back(q);
        }
        return questions;
    }else{
        std::cout << "Error. Couldn't open file: " << filename << std::endl;
        return questions;
    }
}

bool checkAnswer(Question question, std::string chosenAnswer){
    if (chosenAnswer == question.correctAnswer){
        return true;
    }
    else {
        return false;
    }
}