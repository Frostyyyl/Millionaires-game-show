#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "json.hpp"

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