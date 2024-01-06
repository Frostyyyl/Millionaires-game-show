#pragma once
#include <iostream>
#include <memory>
#include "scene.hpp"

class GameOver : public Scene{
public:
    ~GameOver();
    static GameOver& getInstance();
    
    void init() override;
    void start() override;
    void clean() override;

    void processMessage(std::unique_ptr<BaseMessage> msg) override;
private:
    GameOver();
};