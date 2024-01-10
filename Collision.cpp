#include "Collision.hpp"

void CollisionBox::draw(sf::RenderWindow* window){
    if(!visible){
        return;
    }
    sf::RectangleShape rectangle(size);
    rectangle.setFillColor(sf::Color(255, 0, 0, 128));
    rectangle.setPosition(box.getPosition());
    window->draw(rectangle);
}