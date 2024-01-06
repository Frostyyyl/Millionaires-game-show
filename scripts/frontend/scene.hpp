#pragma once
#include <memory>
#include "message.hpp"

class Scene{
public:
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void clean() = 0;

    virtual void processMessage(std::unique_ptr<BaseMessage> msg) = 0;

    virtual ~Scene(){};
};