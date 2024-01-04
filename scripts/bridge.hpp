#pragma once

#include <iostream>
#include <queue>
#include <memory>
#include "message.hpp"


class Bridge{
private:
    std::queue<std::unique_ptr<BaseMessage>> messages;
    Bridge();
    ~Bridge();
public:
    static Bridge& getInstance();
    template <typename... TArgs>
    void addMessage(MessageType messageType, TArgs... args) {
        auto newMessage = std::make_unique<Message<TArgs...>>(messageType, args...);
        messages.push(std::move(newMessage));
    }
    void update();
};
