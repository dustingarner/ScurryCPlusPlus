#include "Sprite.hpp"

void Sprite::addAnimation(string newAnimation, vector<sf::Texture> textures){
    animations[newAnimation] = textures;
    if(currentAnimation == ""){
        currentAnimation = newAnimation;
    }
}

void Sprite::setCurrentAnimation(string animation, int startFrame = 0){
    currentAnimation = animation;
    frame = startFrame;
}

sf::Sprite Sprite::getSprite(){
    sf::Sprite sprite;
    sf::Texture texture = animations.at(currentAnimation)[frame];
    sprite.setTexture(texture);
    return sprite;
}

void Sprite::draw(sf::RenderWindow* window, sf::Vector2f position){
    if(animations.empty()){
        return;
    }
    sf::Sprite sprite = getSprite();
    sprite.setPosition(position + offset);
    window->draw(sprite);
}