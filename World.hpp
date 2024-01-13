#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Input.hpp"
#include "Observer.hpp"
#include "GameObject.hpp"
#include "Mouse.hpp"
#include "Enemy.hpp"

using std::vector;

class World;
class EnemySpawnObserver;

class WorldInitializer{
    public:
    virtual ~WorldInitializer() {}
    virtual void initialize(World* world) = 0;
};

class MainMenuInitializer : public WorldInitializer{
    public:
    virtual void initialize(World* world);
};

class GameInitializer : public WorldInitializer{
    public:
    virtual ~GameInitializer();
    virtual void initialize(World* world);

    private:
    EnemySpawnObserver* spawnObserver;
    //Another observer to add enemies and players
    //Another observer to delete enemies and players?
};

class TestInitializer : public WorldInitializer{
    public:
    virtual void initialize(World* world);
};


class EnemySpawnObserver : public Observer{
    public:
    EnemySpawnObserver(World* _world) : world(_world) {}
    virtual ~EnemySpawnObserver() {}
    virtual void execute(GameObject& object);

    private:
    World* world;
};


class World{
    public:
    World(WorldInitializer* _worldInitializer) : worldInitializer(_worldInitializer) {}
    ~World();
    void initialize() {worldInitializer->initialize(this);}
    void addObject(GameObject* gameObject) {objects.push_back(gameObject);}
    void update(Input* input, double delta);
    void draw(sf::RenderWindow* window);
    void changeScene(WorldInitializer* _worldInitializer);
    void clearObjects();

    private:
    vector<Observer*> observers;
    vector<GameObject*> objects;
    vector<int> deleteQueue;
    WorldInitializer* worldInitializer;


};


#endif