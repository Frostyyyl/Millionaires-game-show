#include "bridge.hpp"
#include "game.hpp"
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

        //msg->print(); // here is printing just in case

        if(msg->getMessageType() > 5){
            std::cout << "got message to backend" << std::endl;
            QuestionsHandler::getInstance().processMessage(std::move(msg));
        }
        else{
            std::cout << "got message to frontend" << std::endl;
            Game::getInstance().processMessage(std::move(msg));
        }

        // if (uniqueMessagePtr->getMessageType() == FRONT_UPDATE) {
        //     Game::getInstance().processMessage(std::move(uniqueMessagePtr));
        // }

        messages.pop();
    }
}