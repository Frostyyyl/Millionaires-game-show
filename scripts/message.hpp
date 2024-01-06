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
    FRONT_GAME_WON,
    // BACK... - messages to backend (from frontend)
    BACK_START_GAME, // get first question (maybe also load all questions here?)
    BACK_ANSWER, // process answer given
    BACK_LIFELINE, // do sth with lifeline (takes also index of lifeline like phone - 1, 50/50 - 2 etc)
    BACK_RESET // reset game
};

class BaseMessage { // base messages to have messages of different types
public:
    virtual ~BaseMessage() = default;
    virtual MessageType getMessageType() const = 0; //so that i can print every message type without dynamic cast
};

template <typename... Args>
class Message : public BaseMessage {
public:
    MessageType type;
    std::tuple<Args...> arguments;

    Message(MessageType t, Args... args) : type(t), arguments(std::move(args)...) {}
    MessageType getMessageType() const override { return type; }
};
