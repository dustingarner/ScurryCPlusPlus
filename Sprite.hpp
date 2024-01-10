#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "SFML/System/Vector2.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

using std::unordered_map, std::string, std::vector;

class Sprite{
    public:
    Sprite() : offset(sf::Vector2f(0.0f,0.0f)), scale(1.0) {}
    Sprite(sf::Vector2f _offset, double _scale) : offset(_offset), scale(_scale) {}
    void setTexture(const string &filePath);
    sf::Sprite getSprite();
    void draw(sf::RenderWindow* window, const sf::Vector2f& position);

    private:
    double scale;
    sf::Texture texture;
    sf::Vector2f offset;
};


#endif