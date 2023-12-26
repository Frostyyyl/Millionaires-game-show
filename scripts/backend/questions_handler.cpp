#include <questions_handler.hpp>

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 g(seed);

QuestionsHandler::QuestionsHandler(const std::string filename){
        questions = loadJSON(filename);
    }

QuestionsHandler::~QuestionsHandler(){};

bool QuestionsHandler::checkAnswer(Question question, std::string chosenAnswer){
    if (chosenAnswer == question.correctAnswer){
        return true;
    }
    else {
        return false;
    }
}

void QuestionsHandler::resetQuestions(){
    availableQuestions = questions;
}

struct Question QuestionsHandler::drawQuestion(int tier){
    std::uniform_int_distribution<int> rng(0, availableQuestions[tier].size()-1);
    int questionIndex = rng(g);
    struct Question question = availableQuestions[tier][questionIndex];
    availableQuestions[tier].erase(availableQuestions[tier].begin() + questionIndex);
    return question;
}

std::pair<std::string, std::vector<std::string>> QuestionsHandler::getQuestion(struct Question question){
    std::string questionText = question.question;
    std::vector<std::string> answers;
    answers.push_back(question.correctAnswer);
    for (int i = 0; i < 3; i++){
        answers.push_back(question.incorrectAnswers[i]);
    }
    std::shuffle(answers.begin(), answers.end(), g);
    return std::pair<std::string, std::vector<std::string>> (questionText, answers);
}