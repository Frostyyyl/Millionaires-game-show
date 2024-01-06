#include "bridge.hpp"
#include "scene_manager.hpp"
#include "questions_handler.hpp"

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
        if(msg->getMessageType() > 6){
            QuestionsHandler::getInstance().processMessage(std::move(msg));
        }
        else{
            SceneManager::getInstance().processMessage(std::move(msg));
        }
        messages.pop();
    }
}