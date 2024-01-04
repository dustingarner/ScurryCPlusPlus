#include "GameObject.hpp"

void MouseObject::update(World& world, Input& input){
    sf::Vector2<double> direction(0,0);
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
    double speedFactor = (double)SPEED * world.getDelta();
    sf::Vector2<double> velocity((double)direction.x * speedFactor, (double)direction.y * speedFactor);
    position += velocity;

    //Scan through enemies from world and check if any are colliding.
}

