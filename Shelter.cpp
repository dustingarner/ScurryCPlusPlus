#include "Shelter.hpp"

void Shelter::initialize(){
    position = sf::Vector2f(650.0, -9.0);
    collision.setPosition(position);
    sprite = Sprite(sf::Vector2f(0.0,0.0), 0.2);
    sprite.setTexture("assets/Shelter.png");
}

void Shelter::update(World* world, Input* input, double delta){
    for(int i = 0; i < allMice.size(); i++){
        if(allMice[i]->collidesWithShelter(collision)){
            removeMouseSubject.notify(*allMice[i]);
            allMice[i]->queueForDelete();
        }
    }

    //First check allMice to see if any overlap
    //Next notify GameInitializer if so
}