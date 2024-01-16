#include "Menu.hpp"

/*
Button::Button(sf::Vector2f _position){
    currentSprite = &mouseOutsideTexture;
}
*/

void Button::setInsideSprite(string fileName){
    mouseInsideSprite = Sprite(sf::Vector2f(0.0,0.0), 0.5);
    mouseInsideSprite.setTexture(fileName);
}

void Button::setOutsideSprite(string fileName){
    mouseOutsideSprite = Sprite(sf::Vector2f(0.0,0.0), 0.5);
    mouseOutsideSprite.setTexture(fileName);
}

void Button::update(World* world, Input* input, double delta){
    collision.setPosition(position);
    if(collision.pointColliding(input->getMousePosition())){
        currentSprite = &mouseInsideSprite;
    }
    else{
        currentSprite = &mouseOutsideSprite;
        return;
    }
    if(input->getMouseJustClicked()){
        isPressed.notify(*this);
    }
}
