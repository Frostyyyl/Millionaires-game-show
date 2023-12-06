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

class ObjectManager{
private:
    std::vector<std::unique_ptr<Object>> objects;
public:
    void update(){
        for(auto& obj : objects) obj->update(); 
    }
    void draw(){
        for(auto& obj : objects) obj->draw();
    }
    template <typename T, typename... Args>
    void addObject(Args&&... args) {
        std::unique_ptr<T> object = std::make_unique<T>(std::forward<Args>(args)...);
        objects.emplace_back(std::move(object));
    }
};