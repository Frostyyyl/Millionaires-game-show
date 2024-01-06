#pragma once
#include <iostream>
#include <memory>
#include "scene.hpp"

class GameWon : public Scene{
public:
    ~GameWon();
    static GameWon& getInstance();
    
    void init() override;
    void start() override;
    void clean() override;

    void processMessage(std::unique_ptr<BaseMessage> msg) override;
private:
    GameWon();
};