#include "Enemy.hpp"

void EnemyObject::initialize(){
    int type = rand() % 2;
    string filePath;
    sf::Vector2f collisionSize;
    sf::Vector2f collisionOffset;
    switch(type){
        case 0:
            filePath = "assets/Cat.png";
            collisionSize = sf::Vector2f(73.68f, 29.4f);
            collisionOffset = sf::Vector2f(88.2f, 57.92f);
            break;
        case 1:
            filePath = "assets/Owl.png";
            collisionSize = sf::Vector2f(37.8f, 55.36f);
            collisionOffset = sf::Vector2f(118.16f, 32.16f);
            break;
    }
    sprite = Sprite(sf::Vector2f(0.0f,0.0f), 0.4);
    sprite.setTexture(filePath);
    collision.setSize(collisionSize);
    collision.setOffset(collisionOffset);

    int location = rand() % 2;
    switch(location){
        case 0:
            direction = sf::Vector2f(-1.0f,-1.0f);
            position.x = (rand()%650) + 150;
            position.y = 600;
            break;
        case 1:
            direction = sf::Vector2f(1.0f,1.0f);
            position.x = (rand()%650);
            position.y = 0;
    }
}

void EnemySpawnerObject::update(World* world, Input* input, double delta){
    if(totalWaitTime >= maxWaitTime){
        spawnSubject.notify(*this);
        totalWaitTime -= maxWaitTime;
    }
    randomizeMaxWaitTime();
    totalWaitTime += SPAWN_SPEED * delta;
}

EnemyObject* spawnEnemy(){
    EnemyObject* newEnemy = new EnemyObject;
    newEnemy->initialize();
    return newEnemy;
}
