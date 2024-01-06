#include "Menu.hpp"

Button::Button(){
    currentSprite = &mouseOutsideTexture;
}

void Button::update(World& world, Input& input){
    sf::Vector2<double> mousePosition((double)input.getMousePosition().x, (double)input.getMousePosition().y);
    if(collision.contains(mousePosition)){
        currentSprite = &mouseInsideTexture;
    }
    else{
        currentSprite = &mouseOutsideTexture;
    }
    if(input.getMouseJustClicked()){
        isPressed.emit();
    }
}
