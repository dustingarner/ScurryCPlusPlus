#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Input.hpp"
#include "GameObject.hpp"

using std::vector;


class World{
    public:
    World(WorldInitializer* _worldInitializer) : worldInitializer(_worldInitializer) {}
    ~World();
    void initialize() {worldInitializer->initialize(this);}
    void addObject(GameObject* gameObject) {objects.push_back(gameObject);}
    void update(Input input, double delta);
    void changeScene(WorldInitializer* _worldInitializer);
    void clearObjects();

    private:
    vector<GameObject*> objects;
    WorldInitializer* worldInitializer;
};

class WorldInitializer{
    public:
    virtual ~WorldInitializer();
    virtual void initialize(World* world) = 0;
};

class MainMenuInitializer : WorldInitializer{
    public:
    virtual void initialize(World* world);
};

class TestInitializer : WorldInitializer{
    public:
    virtual void initialize(World* world);
};


#endif