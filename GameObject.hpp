#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>
#include <stdlib.h>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Input.hpp"
//#include "Observer.hpp"
//#include "World.hpp"
#include "Sprite.hpp"
#include "Collision.hpp"

using std::vector, std::string;

class World;

class GameObject{
    public:
    GameObject() {}
    GameObject(sf::Vector2f _position) : position(_position) {}
    GameObject(sf::Vector2f _position, Sprite _sprite) : position(_position), sprite(_sprite) {}
    virtual ~GameObject() {}
    virtual void initialize() = 0;
    virtual void update(World* world, Input* input, double delta) = 0;
    virtual void draw(sf::RenderWindow* window) {sprite.draw(window, position);}
    bool getQueueDelete() {return queueDelete;}

    protected:
    sf::Vector2f position;
    Sprite sprite;
    bool queueDelete = false;

    private:
    int zIndex;
};








#endif
