#ifndef COLLISION_H
#define COLLISION_H

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Rect.hpp"

class CollisionBox{
    public:
    CollisionBox(sf::Vector2f _size, sf::Vector2f _offset): SIZE(_size), OFFSET(_offset) {}
    void setPosition(sf::Vector2f position) {box = sf::FloatRect(position + OFFSET, SIZE);}
    sf::FloatRect getBox() {return box;}
    
    private:
    sf::FloatRect box;
    const sf::Vector2f SIZE;
    const sf::Vector2f OFFSET;
};

#endif

