#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Input.hpp"

class World{
    public:
    virtual ~World();
    virtual void update() = 0;
    double getDelta(){return delta;}

    private:
    double delta;
};

class GameObject{
    public:
    virtual ~GameObject();
    virtual void update(World& world, Input& input) = 0;
    virtual sf::Sprite getCurrentSprite() = 0; //Probably pass in the screen and screen size or whatever

    protected:
    sf::Vector2<double> position;

    private:
    int zIndex;
};

class MouseObject : GameObject{
    public:
    virtual void update(World& world, Input& input);
    virtual void getCurrentSprite();

    private:
    const int SPEED = 300.0;
};

#endif