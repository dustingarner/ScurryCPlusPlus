#ifndef MOUSE_H
#define MOUSE_H

#include "GameObject.hpp"
#include "Observer.hpp"


class MouseObject : public GameObject{
    public:
    MouseObject(sf::Vector2f _position) : GameObject(_position) {}
    virtual void initialize();
    sf::Vector2f getDirection(Input* input);
    virtual void update(World* world, Input* input, double delta);
    virtual void draw(sf::RenderWindow* window);
    virtual bool getInfo() {return getCaptured();}
    void setControllable(bool toggle) {controllable = toggle;}
    void setPosition(sf::Vector2f _position);
    void incrementPosition(sf::Vector2f velocity);
    bool collidesWithEnemy(CollisionBox& testCollision) {return enemyCollision.rectColliding(testCollision);}
    bool collidesWithShelter(CollisionBox& testCollision) {return shelterCollision.rectColliding(testCollision);}
    void makeCaptured();
    bool getCaptured() {return captured;}
    void addClickObserver(Observer* observer) {isClicked.addObserver(observer);}

    private:
    bool controllable = false;
    bool captured = false;
    const int SPEED = 125.0;
    Subject isClicked = Subject();
    CollisionBox enemyCollision = CollisionBox(sf::Vector2f(50.0, 25.0), sf::Vector2f(0.0,0.0));
    CollisionBox shelterCollision = CollisionBox(sf::Vector2f(75.0, 36.0), sf::Vector2f(-22.3, -9.85));
    CollisionBox cursorCollision = CollisionBox(sf::Vector2f(131.25, 75.0), sf::Vector2f(-70.0, -28.75));
};

MouseObject* makeMouse(sf::Vector2f position, bool controllable = false);


#endif