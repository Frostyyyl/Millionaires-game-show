#pragma once
#include <tuple>
#include <iostream> 

enum MessageType{
    // FRONT... - messages to frontend (from backend)
    FRONT_START_GAME, // start game and show first question
    FRONT_NEXT_QUESTION, // show next question
    FRONT_50_50, // hide two questions after lifeline
    FRONT_PHONE, // show phone answer
    FRONT_AUDIENCE, // show audience answer
    FRONT_GAME_OVER, // show game over screen
    // BACK... - messages to backend (from frontend)
    BACK_START_GAME, // get first question (maybe also load all questions here?)
    BACK_ANSWER, // process answer given
    BACK_LIFELINE, // do sth with lifeline (takes also index of lifeline like phone - 1, 50/50 - 2 etc)
    BACK_RESET // reset game
};

class BaseMessage { // base messages to have messages of different types
public:
    virtual ~BaseMessage() = default;
    virtual void print() const = 0;
    virtual MessageType getMessageType() const = 0; //so that i can print every message type without dynamic cast
};

template <typename... Args>
class Message : public BaseMessage {
public:
    MessageType type;
    std::tuple<Args...> arguments;

    Message(MessageType t, Args... args) : type(t), arguments(std::move(args)...) {}

    void print() const override {
        std::cout << "Message Type: " << type << std::endl;
        std::cout << "Arguments: ";
        printTuple(arguments);
    }

    MessageType getMessageType() const override { return type; }

private:
    // printing
    template <typename... TupleArgs>
    void printTuple(const std::tuple<TupleArgs...>& t) const {
        std::apply([](const auto&... args) {
            ((std::cout << args << " "), ...);
            std::cout << std::endl;
        }, t);
    }
};
