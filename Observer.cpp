#include "Observer.hpp"

Subject::~Subject(){
    for(int i = 0; i < observers.size(); i++){
        delete observers[i];
    }
    observers.clear();
}

void Subject::notify(GameObject& object){
    for(int i = 0; i < observers.size(); i++){
        observers[i]->execute(object);
    }
}

void Subject::removeObserver(Observer* observer){
    for(int i = 0; i < observers.size(); i++){
        if(observer == observers[i]){
            delete observers[i];
            observers.erase(observers.begin()+i);
            break;
        }
    }
}