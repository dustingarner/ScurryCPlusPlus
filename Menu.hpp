#ifndef MENU_H
#define MENU_H

#include <string>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"
#include "Observer.hpp"

using std::string;

class Button : public GameObject{
    public:
    Button(sf::Vector2f _position) : GameObject(_position) {}
    virtual ~Button() {}
    void setInsideSprite(string fileName);
    void setOutsideSprite(string fileName);
    virtual void initialize() {currentSprite = &mouseOutsideSprite; collision.setPosition(position);}
    virtual void update(World* world, Input* input, double delta);
    virtual void draw(sf::RenderWindow* window) {currentSprite->draw(window, position);}
    Sprite* getCurrentSprite(){return currentSprite;}
    void addObserver(Observer* observer) {isPressed.addObserver(observer);}

    private:
    Sprite* currentSprite;
    Sprite mouseOutsideSprite;
    Sprite mouseInsideSprite;
    CollisionBox collision = CollisionBox(sf::Vector2f(160.0, 90.0), sf::Vector2f(0.0,0.0));
    Subject isPressed = Subject();
};

#endif