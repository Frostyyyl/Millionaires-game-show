#pragma once
#include <iostream>
#include <vector>
#include <memory>

class Object{
private:
    bool active = true;
public:
    ~Object(){};
    virtual void update() = 0;
    virtual void draw() = 0;
    bool isActive(){ return active; }
    void destroy(){ active = false; }
};

class Manager{
private:
    std::vector<std::unique_ptr<Object>> objects;
public:
    void update(){
        for(auto& obj : objects) obj->update(); 
    }
    void draw(){
        for(auto& obj : objects) obj->draw();
    }
    Object& addObject(){
        
    }
};