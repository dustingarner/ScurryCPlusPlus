#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

using std::vector;

class Observer{
    public:
    Observer();
};

class Subject{
    public:
    Subject();
    ~Subject(){}
    void emit();
};

#endif