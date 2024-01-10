#include "Sprite.hpp"


void Sprite::setTexture(const string &filePath){
    texture.loadFromFile(filePath);
}

sf::Sprite Sprite::getSprite(){
    sf::Sprite sprite;
    sprite.setTexture(texture);
    return sprite;
}

void Sprite::draw(sf::RenderWindow* window, const sf::Vector2f& position){
    sf::Sprite sprite = getSprite();
    sprite.setPosition(position + offset);
    sprite.scale(scale, scale);
    window->draw(sprite);
}
