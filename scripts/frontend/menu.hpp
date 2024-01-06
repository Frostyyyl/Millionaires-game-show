#pragma once
#include <iostream>
#include <memory>
#include "scene.hpp"

class MainMenu : public Scene{
public:
    ~MainMenu();
    static MainMenu& getInstance();
    
    void init() override;
    void start() override;
    void clean() override;

    void processMessage(std::unique_ptr<BaseMessage> msg) override;
private:
    MainMenu();
};