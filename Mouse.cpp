#include "Mouse.hpp"

void MouseObject::initialize(){
    sprite = Sprite(sf::Vector2f(-70.0,-28.75), 0.25);
    sprite.setTexture("assets/Mouse.png");
    setPosition(position);
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

void MouseObject::setPosition(sf::Vector2f _position){
    position = _position;
    enemyCollision.setPosition(position);
    shelterCollision.setPosition(position);
    cursorCollision.setPosition(position);
}

void MouseObject::incrementPosition(sf::Vector2f velocity){
    position+=velocity;
    enemyCollision.setPosition(position);
    shelterCollision.setPosition(position);
    cursorCollision.setPosition(position);
}

void MouseObject::makeCaptured(){
    captured = true;
    enemyCollision.setColliding(false);
    shelterCollision.setColliding(false);
    cursorCollision.setColliding(false);
}

void MouseObject::update(World* world, Input* input, double delta){
    if(captured){
        return;
    }
    sf::Vector2f cursorPosition = input->getMousePosition();
    bool mouseClicked = input->getMouseClicked();
    if(mouseClicked && cursorCollision.pointColliding(cursorPosition)){
        isClicked.notify(*this);
        controllable = true;
    }
    if(!controllable){
        return;
    }
    sf::Vector2f direction = getDirection(input);
    double speedFactor = (double)SPEED * delta;
    sf::Vector2f velocity(direction.x * (float)speedFactor, direction.y * (float)speedFactor);
    setPosition(position + velocity);
}


void MouseObject::draw(sf::RenderWindow* window){
    sprite.draw(window, position);
    //enemyCollision.draw(window);
    //shelterCollision.draw(window);
    //cursorCollision.draw(window);
}


MouseObject* makeMouse(sf::Vector2f position, bool controllable){
    MouseObject* mouse = new MouseObject(position);
    mouse->initialize();
    mouse->setControllable(controllable);
    return mouse;
}
