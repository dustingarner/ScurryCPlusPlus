#ifndef INPUT_H
#define INPUT_H

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

class Input{
    public:
    Input() : _prevClicked(false) {}
    Input(bool prevClicked) : _prevClicked(prevClicked) {}
    void initialize(sf::RenderWindow* window);
    bool getMouseClicked() {return mouseClicked;}
    sf::Vector2f getMousePosition() {return mousePos;}
    bool getMouseJustClicked() {return mouseJustClicked;}
    bool isLeftPressed() {return directions[0];}
    bool isRightPressed() {return directions[1];}
    bool isUpPressed() {return directions[2];}
    bool isDownPressed() {return directions[3];}

    private:
    bool directions[4];
    const bool _prevClicked;
    bool mouseJustClicked;
    bool mouseClicked;
    sf::Vector2f mousePos;
};


#endif
