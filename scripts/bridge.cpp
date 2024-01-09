#include "bridge.hpp"
#include "scene_manager.hpp"
#include "questions_handler.hpp"
#include "lifelines.hpp"

Bridge::Bridge(){}

Bridge::~Bridge(){}

Bridge &Bridge::getInstance()
{
    static Bridge INSTANCE;
    return INSTANCE;
}

void Bridge::update() {
    while (!messages.empty()) {
        auto msg = std::move(messages.front());
        if (msg->getMessageType() < 8){
            SceneManager::getInstance().processMessage(std::move(msg));
        } else if(msg->getMessageType() == 10){
            Half::getInstance().processMessage(std::move(msg));
        } else if (msg->getMessageType() == 11){
            Phone::getInstance().processMessage(std::move(msg));
        } else if (msg->getMessageType() == 12){
            Audience::getInstance().processMessage(std::move(msg));
        } 
        else{
            QuestionsHandler::getInstance().processMessage(std::move(msg));
        }
        messages.pop();
    }
}