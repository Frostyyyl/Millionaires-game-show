#include "bridge.hpp"
#include "game.hpp"

Bridge::Bridge(){}

Bridge::~Bridge(){}

Bridge &Bridge::getInstance()
{
    static Bridge INSTANCE;
    return INSTANCE;
}

void Bridge::update() {
    while (!messages.empty()) {
        auto uniqueMessagePtr = std::move(messages.front());

        //uniqueMessagePtr->print(); // here is printing just in case

        if (uniqueMessagePtr->getMessageType() == FRONT_UPDATE) {
            Game::getInstance().processMessage(std::move(uniqueMessagePtr));
        }

        messages.pop();
    }
}