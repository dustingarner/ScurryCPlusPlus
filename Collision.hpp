#ifndef COLLISION_H
#define COLLISION_H

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

class CollisionBox{
    public:
    CollisionBox(): size(sf::Vector2f(0.0f,0.0f)), offset(sf::Vector2f(0.0f,0.0f)) {}
    CollisionBox(sf::Vector2f _size, sf::Vector2f _offset): size(_size), offset(_offset) {}
    void setSize(sf::Vector2f _size) {size = _size;}
    void setOffset(sf::Vector2f _offset) {offset = _offset;}
    void setPosition(sf::Vector2f position) {box = sf::FloatRect(position + offset, size);}
    sf::FloatRect getBox() {return box;}
    void setVisible(bool toggle) {visible = toggle;}
    bool pointColliding(sf::Vector2f point) {if(!collides){return false;} return box.contains(point);}
    bool rectColliding(CollisionBox& otherBox) 
            {if(!collides){return false;} return box.intersects(otherBox.getBox());}
    void draw(sf::RenderWindow* window);
    void setColliding(bool toggle) {collides = toggle;}
    
    private:
    bool visible = true;
    bool collides = true;
    sf::FloatRect box;
    sf::Vector2f size;
    sf::Vector2f offset;
};

#endif

