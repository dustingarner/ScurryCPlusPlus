#include "GameObject.hpp"


void MouseObject::update(World& world, Input& input, double delta){
    sf::Vector2f direction(0.0,0.0);
    if(input.isLeftPressed()){
        direction.x -= 1.0;
    }
    if(input.isRightPressed()){
        direction.x += 1.0;
    }
    if(input.isUpPressed()){
        direction.y -= 1.0;
    }
    if(input.isDownPressed()){
        direction.y += 1.0;
    }
    double speedFactor = (double)SPEED * delta;
    sf::Vector2f velocity(direction.x * (float)speedFactor, direction.y * (float)speedFactor);
    position += velocity;

    //Scan through enemies from world and check if any are colliding.
}

MouseObject makeMouse(sf::Vector2f position){
    Sprite sprite(sf::Vector2f(0.0,0.0));
    vector<sf::Texture> textures = {sf::Texture()};
    textures[0].loadFromFile("assets/Mouse.png");
    sprite.addAnimation("default", textures);
    return MouseObject(position, sprite);
}

