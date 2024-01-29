#ifndef TIMER_H
#define TIMER_H

#include "GameObject.hpp"
#include "Observer.hpp"


class TimerObject : public GameObject{
    public:
    TimerObject(double _duration) : duration(_duration) {}
    virtual ~TimerObject() {}
    virtual void initialize() {}
    virtual void update(World* world, Input* input, double delta);
    void addObserver(Observer* observer) {timeoutSubject.addObserver(observer);}

    private:
    bool isOn = true;
    double duration;
    Subject timeoutSubject = Subject();
    double timeElapsed = 0.0;
};



#endif