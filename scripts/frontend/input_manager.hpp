#pragma once

#include <iostream>
#include <vector>
#include "button_system.hpp"

class InputManager{
private:
    std::vector<ButtonBase*> buttons;
public:
    void update();
    void addButton(ButtonBase* button);
    void clear();
};