#pragma once
#include <iostream>
#include <memory>
#include "SDL.h"
#include "scene.hpp"

class Game : public Scene{
public:
    ~Game();
    static Game& getInstance();
    
    void init() override;
    void start() override;
    void clean() override;

    void processMessage(std::unique_ptr<BaseMessage> msg) override;
private:
    Game();
};