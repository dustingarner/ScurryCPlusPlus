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

using std::vector;


class GameObject{
    public:
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
    MouseObject(sf::Vector2f _position, Sprite _sprite) : GameObject(_position, _sprite) {}
    virtual void update(World& world, Input& input, double delta);
    virtual sf::Sprite getCurrentSprite();

    private:
    const int SPEED = 300.0;
};

MouseObject makeMouse();


#endif