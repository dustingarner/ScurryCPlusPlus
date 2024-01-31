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
    void addCaptureObserver(Observer* observer) {captureMouseSubject.addObserver(observer);}
    void addRemoveObserver(Observer* observer) {removeMouseSubject.addObserver(observer);}

    private:
    int speed;
    CollisionBox collision;
    sf::Vector2f direction;
    vector<MouseObject*> capturedMice;
    const vector<MouseObject*>& allMice;
    Subject captureMouseSubject = Subject();
    Subject removeMouseSubject = Subject();
};



class EnemySpawnerObject : public GameObject{
    public:
    EnemySpawnerObject() {}
    ~EnemySpawnerObject() {}
    virtual void initialize();
    virtual void update(World* world, Input* input, double delta);
    virtual void draw(sf::RenderWindow* window) {}
    void randomizeMaxWaitTime() {maxWaitTime = 200.0 + (double)(rand() % 100);}
    void connectObserver(Observer* observer) {spawnSubject.addObserver(observer);}
    void turnOn() {isOn = true;}
    Observer* getTurnOnObserver() {return turnOnObserver;}
    
    private:
    bool isOn = false;
    const double SPAWN_SPEED = 100.0;
    double totalWaitTime = 0.0;
    double maxWaitTime;
    Observer* turnOnObserver;
    Subject spawnSubject = Subject();
};

class SpawnOnObserver : public Observer{
    public:
    SpawnOnObserver(EnemySpawnerObject* _spawner) : spawner(_spawner) {}
    virtual ~SpawnOnObserver() {}
    virtual void execute(GameObject& object) {spawner->turnOn();}

    private:
    EnemySpawnerObject* spawner;
};



EnemyObject* spawnEnemy(const vector<MouseObject*>& allMice, Observer* mouseRemoveObserver);

#endif