#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "Input.hpp"
#include "World.hpp"
#include "Sprite.hpp"
#include "Collision.hpp"

using std::vector;


class GameObject{
    public:
    GameObject(sf::Vector2f _position) : position(_position) {}
    GameObject(sf::Vector2f _position, Sprite _sprite) : position(_position), sprite(_sprite) {}
    virtual ~GameObject();
    virtual void update(World& world, Input& input, double delta) = 0;
    virtual void draw(sf::RenderWindow* window) {sprite.draw(window, position);}

    protected:
    sf::Vector2f position;
    Sprite sprite;

    private:
    int zIndex;
};


class MouseObject : GameObject{
    public:
    MouseObject(sf::Vector2f _position) : GameObject(_position) {}
    virtual void update(World& world, Input& input, double delta);
    virtual sf::Sprite getCurrentSprite();
    void setControllable(bool toggle) {controllable = toggle;}

    private:
    bool controllable = false;
    const int SPEED = 300.0;
    CollisionBox enemyCollision = CollisionBox(sf::Vector2f(50.0, 25.0), sf::Vector2f(0.0,0.0));
    CollisionBox shelterCollision = CollisionBox(sf::Vector2f(75.0, 36.0), sf::Vector2f(-22.3, -9.85));
    CollisionBox cursorCollision = CollisionBox(sf::Vector2f(131.25, 75.0), sf::Vector2f(-70.0, -28.75));
};

MouseObject makeMouse();


#endif
