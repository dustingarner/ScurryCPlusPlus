#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include "GameObject.hpp"

using std::vector;

class Observer{
    public:
    virtual ~Observer() {}
    virtual void execute(GameObject& object) = 0;
};

class Subject{
    public:
    Subject() {}
    ~Subject() {}
    virtual void notify(GameObject& object);
    void addObserver(Observer* observer) {observers.push_back(observer);}
    void removeObserver(Observer* observer);

    private:
    vector<Observer*> observers;
};

#endif