#ifndef MENU_H
#define MENU_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "GameObject.hpp"
#include "Observer.hpp"

class Button : GameObject{
    public:
    Button(sf::Vector2f _position) : GameObject(_position) {}
    virtual void update(World& world, Input& input);
    void setOutsideTexture(sf::Texture texture){mouseOutsideTexture.setTexture(texture);}
    void setInsideTexture(sf::Texture texture){mouseInsideTexture.setTexture(texture);}
    sf::Sprite getCurrentSprite(){return *currentSprite;}

    private:
    sf::Sprite* currentSprite;
    sf::Sprite mouseOutsideTexture;
    sf::Sprite mouseInsideTexture;
    sf::Rect<double> collision;
    Subject isPressed;
};

#endif