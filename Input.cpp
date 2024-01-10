#include <iostream>
#include "Input.hpp"

void Input::initialize(sf::RenderWindow* window){
    directions[0] = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    directions[1] = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    directions[2] = sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    directions[3] = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    
    mouseClicked = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    mouseJustClicked = !_prevClicked && mouseClicked;

    sf::Vector2i tempMousePosition = sf::Mouse::getPosition(*window);
    mousePos = sf::Vector2f((double)tempMousePosition.x, (double)tempMousePosition.y);
}

