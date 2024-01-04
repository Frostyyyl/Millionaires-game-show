#pragma once
#include <tuple>
#include <iostream> 

enum MessageType{
    FRONT_UPDATE,
    FRONT_SHOW_QUESTION,
    BACK_UPDATE,
    BACK_ANSWER
};

class BaseMessage {
public:
    virtual ~BaseMessage() = default;
    virtual void print() const = 0;
    virtual MessageType getMessageType() const = 0;
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
