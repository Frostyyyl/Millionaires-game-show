#pragma once
#include <vector>
#include "SDL.h"

struct Position{
    int x, y;
    Position() : x(0), y(0){}
    Position(int x, int y) : x(x), y(y){}
};

class Object{
protected:
    Position pos; 
public:
    Object(){}
    Object(int x, int y) : pos(x, y){}
    ~Object(){}
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void destroy() = 0;
};

class ObjectManager{
private:
    std::vector<Object*> objects;
public:
    void update(){
        for(auto& obj : objects) obj->update();
    }
    void draw(){
        for(auto& obj : objects) obj->draw();
    }
    void addObject(Object* obj){
        objects.emplace_back(obj);
    }
    void clear(){
        objects.clear();
    }
    void erase(Object* obj){
        for (int i = 0; i < objects.size(); i++){
            if (objects[i] == obj){
                objects.erase(objects.begin() + i);
            }
        }
    }
};

class Mouse : public Object{
private:
    static SDL_Rect pointer;
public:
    Mouse(){
        pointer.w = pointer.h = 1;
    };
    void update(){
        SDL_GetMouseState(&pointer.x, &pointer.y); 
    }
    void draw(){};
    static SDL_Rect& getPosition(){ return pointer; }
    void destroy() override{ this->~Mouse();}
};