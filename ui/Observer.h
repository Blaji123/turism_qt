//
// Created by Blajan David on 4/26/2024.
//

#ifndef TURISM_QT_OBSERVER_H
#define TURISM_QT_OBSERVER_H

#include <vector>
#include <algorithm>

class Observer{
public:
    virtual void update() = 0;
};

class Observable{
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* obs){
        observers.push_back(obs);
    }
    void removeObserver(Observer* obs){
        observers.erase(std::remove(observers.begin(), observers.end(),obs), observers.end());
    }
    void notify(){
        for(auto obs : observers){
            obs->update();
        }
    }
};

#endif //TURISM_QT_OBSERVER_H
