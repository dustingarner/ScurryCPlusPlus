#ifndef SHELTER_H
#define SHELTER_H

#include "GameObject.hpp"
#include "Observer.hpp"
#include "Mouse.hpp"
#include "Collision.hpp"

class Shelter : public GameObject{
    public:
    Shelter(const vector<MouseObject*>& _allMice) : allMice(_allMice) {}
    virtual void initialize();
    virtual void update(World* world, Input* input, double delta);
    virtual void draw(sf::RenderWindow* window) {sprite.draw(window, position); collision.draw(window);}
    int getScore() {return score;}
    void addRemoveObserver(Observer* observer) {removeMouseSubject.addObserver(observer);}

    private:
    int score = 0;
    CollisionBox collision = CollisionBox(sf::Vector2f(37.6, 35.2), sf::Vector2f(48.8,38.4));
    const vector<MouseObject*>& allMice;
    Subject removeMouseSubject = Subject();
};



#endif