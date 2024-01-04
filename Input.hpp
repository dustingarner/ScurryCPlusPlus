#ifndef INPUT_H
#define INPUT_H

#include "SFML/System/Vector2.hpp"

class Input{
    public:
    Input() : _prevClicked(false) {}
    Input(bool prevClicked) : _prevClicked(prevClicked) {}
    ~Input() {}
    void init();
    bool getMouseClicked(){return mouseClicked;}
    sf::Vector2i getMousePosition(){return mousePos;}
    bool getMouseJustClicked(){return mouseJustClicked;}
    bool isLeftPressed(){return directions[0];}
    bool isRightPressed(){return directions[1];}
    bool isUpPressed(){return directions[2];}
    bool isDownPressed(){return directions[3];}

    private:
    bool directions[4];
    const bool _prevClicked;
    bool mouseJustClicked;
    bool mouseClicked;
    sf::Vector2i mousePos;
};


#endif
