#include "World.hpp"

World::~World(){
    clearObjects();
}

void World::clearObjects(){
    for(int i = 0; i < objects.size(); i++){
        delete objects[i];
    }
    objects = {};
}

void World::changeScene(WorldInitializer* _worldInitializer){
    clearObjects();
    if(worldInitializer != nullptr){
        delete worldInitializer;
    }
    worldInitializer = _worldInitializer;
    worldInitializer->initialize(this);
}

void World::update(Input input, double delta){
    for(int i = 0; i < objects.size(); i++){
        objects[i]->update(*this, input, delta);
    }
}


void TestInitializer::initialize(World* world){
    
}