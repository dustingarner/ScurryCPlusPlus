#include <iostream>
#include "GameObject.hpp"


void MouseObject::initialize(){
    sprite = Sprite(sf::Vector2f(-70.0,-28.75), 0.25);
    sprite.setTexture("assets/Mouse.png");
}

sf::Vector2f MouseObject::getDirection(Input* input){
    sf::Vector2f direction(0.0,0.0);
    if(!controllable){
        return direction;
    }
    if(input->isLeftPressed()){
        direction.x -= 1.0;
    }
    if(input->isRightPressed()){
        direction.x += 1.0;
    }
    if(input->isUpPressed()){
        direction.y -= 1.0;
    }
    if(input->isDownPressed()){
        direction.y += 1.0;
    }
    if(direction.x == 0 && direction.y == 0){
        return direction;
    }
    double magnitude = sqrt(pow(direction.x, 2.0) + pow(direction.y, 2.0));
    direction.x /= magnitude;
    direction.y /= magnitude;
    return direction;
}

void MouseObject::update(World* world, Input* input, double delta){
    sf::Vector2f direction = getDirection(input);
    double speedFactor = (double)SPEED * delta;
    sf::Vector2f velocity(direction.x * (float)speedFactor, direction.y * (float)speedFactor);
    position += velocity;

    enemyCollision.setPosition(position);
    shelterCollision.setPosition(position);
    cursorCollision.setPosition(position);
}



 void MouseObject::draw(sf::RenderWindow* window){
    sprite.draw(window, position);
    //enemyCollision.draw(window);
    //shelterCollision.draw(window);
    //cursorCollision.draw(window);
}


void EnemyObject::initialize(){
    int type = rand() % 2;
    string filePath;
    sf::Vector2f collisionSize;
    sf::Vector2f collisionOffset;
    switch(type){
        case 0:
            filePath = "assets/Cat.png";
            collisionSize = sf::Vector2f(73.68f, 29.4f);
            collisionOffset = sf::Vector2f(88.2f, 57.92f);
            break;
        case 1:
            filePath = "assets/Owl.png";
            collisionSize = sf::Vector2f(37.8f, 55.36f);
            collisionOffset = sf::Vector2f(118.16f, 32.16f);
            break;
    }
    sprite = Sprite(sf::Vector2f(0.0f,0.0f), 0.4);
    sprite.setTexture(filePath);
    collision.setSize(collisionSize);
    collision.setOffset(collisionOffset);

    int location = rand() % 2;
    switch(location){
        case 0:
            direction = sf::Vector2f(-1.0f,-1.0f);
            position.x = (rand()%650) + 150;
            position.y = 600;
            break;
        case 1:
            direction = sf::Vector2f(1.0f,1.0f);
            position.x = (rand()%650);
            position.y = 0;
    }
}

//Enemy update
//Stuff about enemy spawner


MouseObject* makeMouse(sf::Vector2f position, bool controllable){
    MouseObject* mouse = new MouseObject(position);
    mouse->initialize();
    mouse->setControllable(controllable);
    return mouse;
}

