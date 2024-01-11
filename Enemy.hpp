#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.hpp"
#include "Observer.hpp"


class EnemyObject : public GameObject{
    public:
    EnemyObject() : GameObject() {}
    virtual void initialize();
    virtual void update(World* world, Input* input, double delta);
    virtual void draw(sf::RenderWindow* window);

    private:
    int speed;
    CollisionBox collision;
    sf::Vector2f direction;
};

class EnemySpawnerObject : public GameObject{
    public:
    EnemySpawnerObject() : GameObject() {}
    ~EnemySpawnerObject() {}
    virtual void initialize() {randomizeMaxWaitTime();}
    virtual void update(World* world, Input* input, double delta);
    virtual void draw(sf::RenderWindow* window) {}
    void randomizeMaxWaitTime() {maxWaitTime = 200.0 + (double)(rand() % 100);}
    void connectObserver(Observer* observer) {spawnSubject.addObserver(observer);}

    private:
    const double SPAWN_SPEED = 200.0;
    double totalWaitTime = 0.0;
    double maxWaitTime;
    Subject spawnSubject = Subject();

};

EnemyObject* spawnEnemy();

#endif