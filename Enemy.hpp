#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.hpp"
#include "Observer.hpp"
#include "Mouse.hpp"
#include "Collision.hpp"


class EnemyObject : public GameObject{
    public:
    EnemyObject(const vector<MouseObject*>& _allMice) : allMice(_allMice) {}
    ~EnemyObject() {}
    virtual void initialize();
    virtual void update(World* world, Input* input, double delta);
    virtual void draw(sf::RenderWindow* window) {sprite.draw(window, position);}
    void captureMouse(MouseObject* mouse);
    void attemptDeletion();
    void attemptCapture();
    void addRemoveObserver(Observer* observer) {removeMouseSubject.addObserver(observer);}

    private:
    int speed;
    CollisionBox collision;
    sf::Vector2f direction;
    vector<MouseObject*> capturedMice;
    const vector<MouseObject*>& allMice;
    Subject removeMouseSubject = Subject();
};

class EnemySpawnerObject : public GameObject{
    public:
    EnemySpawnerObject() {}
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

EnemyObject* spawnEnemy(const vector<MouseObject*>& allMice, Observer* mouseRemoveObserver);

#endif