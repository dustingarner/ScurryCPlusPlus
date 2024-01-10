#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <stdlib.h>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Input.hpp"
//#include "World.hpp"
#include "Sprite.hpp"
#include "Collision.hpp"

using std::vector, std::string;

class World;

class GameObject{
    public:
    GameObject(sf::Vector2f _position) : position(_position) {}
    GameObject(sf::Vector2f _position, Sprite _sprite) : position(_position), sprite(_sprite) {}
    virtual ~GameObject() {}
    virtual void initialize() = 0;
    virtual void update(World* world, Input* input, double delta) = 0;
    virtual void draw(sf::RenderWindow* window) {sprite.draw(window, position);}

    protected:
    sf::Vector2f position;
    Sprite sprite;

    private:
    int zIndex;
};


class MouseObject : public GameObject{
    public:
    MouseObject(sf::Vector2f _position) : GameObject(_position) {}
    virtual void initialize();
    sf::Vector2f getDirection(Input* input);
    virtual void update(World* world, Input* input, double delta);
    virtual void draw(sf::RenderWindow* window);
    void setControllable(bool toggle) {controllable = toggle;}

    private:
    bool controllable = false;
    const int SPEED = 300.0;
    CollisionBox enemyCollision = CollisionBox(sf::Vector2f(50.0, 25.0), sf::Vector2f(0.0,0.0));
    CollisionBox shelterCollision = CollisionBox(sf::Vector2f(75.0, 36.0), sf::Vector2f(-22.3, -9.85));
    CollisionBox cursorCollision = CollisionBox(sf::Vector2f(131.25, 75.0), sf::Vector2f(-70.0, -28.75));
};

class EnemyObject : public GameObject{
    public:
    EnemyObject(sf::Vector2f _position) : GameObject(_position) {}
    virtual void initialize();
    virtual void update(World* world, Input* input, double delta);
    virtual void draw(sf::RenderWindow* window);

    private:
    int speed;
    CollisionBox collision;
    sf::Vector2f direction;
};


MouseObject* makeMouse(sf::Vector2f position, bool controllable = false);

#endif
