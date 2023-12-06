#pragma once
#include <iostream>

class Position{
private:
    int xpos, ypos;
public:
    Position(){
        xpos = 0;
        ypos = 0;
    }
    Position(int x, int y){
        xpos = x;
        ypos = y;
    }
    int getX(){
        return xpos;
    }
    void setX(int x){
        xpos = x;
    }
    int getY(){
        return ypos;
    }
    void setY(int y){
        ypos = y;
    }
};