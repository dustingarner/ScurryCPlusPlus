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

void World::update(Input* input, double delta){
    for(int i = 0; i < objects.size(); i++){
        objects[i]->update(this, input, delta);
    }
}

void World::draw(sf::RenderWindow* window){
    window->clear();
    //Sort objects here
    for(int i = 0; i < objects.size(); i++){
        objects[i]->draw(window);
    }
    window->display();
}


void TestInitializer::initialize(World* world){
    world->addObject(makeMouse(sf::Vector2f(100.0f, 100.0f), true));
}

//pg.Vector2(100, 500), pg.Vector2(200, 500), pg.Vector2(100, 400), pg.Vector2(200, 400)