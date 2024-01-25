#include "GameObject.hpp"


SpriteObject::SpriteObject(sf::Vector2f _position, string _textureFilePath, sf::Vector2f _offset, double _scale): 
        textureFilePath(_textureFilePath), offset(_offset), scale(_scale){
    position = _position;
}

void SpriteObject::initialize(){
    sprite = Sprite(offset, scale);
    sprite.setTexture(textureFilePath);
}
