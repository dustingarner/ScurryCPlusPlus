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
    Sprite(sf::Vector2f _offset) : offset(_offset) {}
    void addAnimation(string newAnimation, vector<sf::Texture> textures);
    void setCurrentAnimation(string animation, int startFrame = 0);
    sf::Sprite getSprite();
    void draw(sf::RenderWindow* window, sf::Vector2f position);

    private:
    string currentAnimation = "";
    int frame = 0;
    sf::Vector2f offset;
    unordered_map<string, vector<sf::Texture>> animations;
};


#endif