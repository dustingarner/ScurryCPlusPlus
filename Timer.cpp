#include "Timer.hpp"

void TimerObject::update(World* world, Input* input, double delta){
    if(!isOn){
        return;
    }
    timeElapsed += delta;
    if(timeElapsed >= duration){
        timeoutSubject.notify(*this);
        isOn = false;
    }
}
