#include "World.hpp"

GameInitializer::~GameInitializer(){
    delete spawnObserver;
    delete mouseClickObserver;
    delete mouseRemoveObserver;
    //delete other things
}

void GameInitializer::initialize(World* world){
    world->resetScore();
    mouseClickObserver = new MouseClickObserver(this);
    mouseRemoveObserver = new MouseRemoveObserver(this);
    allMice.push_back(makeMouse(sf::Vector2f(100.0f, 500.0f), true));
    allMice.push_back(makeMouse(sf::Vector2f(200.0f, 500.0f), false));
    allMice.push_back(makeMouse(sf::Vector2f(100.0f, 400.0f), false));
    allMice.push_back(makeMouse(sf::Vector2f(200.0f, 400.0f), false));
    for(int i = 0; i < allMice.size(); i++){
        allMice[i]->addClickObserver(mouseClickObserver);
        world->addObject(allMice[i]);
    }
    spawnObserver = new EnemySpawnObserver(world, allMice, mouseRemoveObserver);
    EnemySpawnerObject* spawner = new EnemySpawnerObject();
    spawner->connectObserver(spawnObserver);
    world->addObject(spawner);
    
    Shelter* shelter = new Shelter(allMice); //Make this into a function?
    shelter->initialize();
    shelter->addRemoveObserver(mouseRemoveObserver);
    world->addObject(shelter);
}

void GameInitializer::uncontrolMice(){
    for(int i = 0; i < allMice.size(); i++){
        allMice[i]->setControllable(false);
    }
}

void GameInitializer::removeMouse(GameObject& mouse){
    for(int i = 0; i < allMice.size(); i++){
        if(&mouse == allMice[i]){
            allMice.erase(allMice.begin()+i);
            break;
        }
    }
    if(!mouse.getInfo()){
        score++;
    }
    if(allMice.size() == 0){
        endGame();
    }
}

#include <iostream>
void GameInitializer::endGame(){
    switch(score){
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
    }
    std::cout<<score;
}

void EnemySpawnObserver::execute(GameObject& object){
    EnemyObject* newEnemy = spawnEnemy(allMice, mouseRemoveObserver);
    //Connect EnemyObject to erasing itself in time
    world->addObject(newEnemy);
}


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

void World::attemptSceneChange(){
    switch(newScene){
        case NONE:
            break;
        case MAIN:
            changeScene(new MainMenuInitializer);
            break;
        case INFO:
            changeScene(new InfoInitializer);
            break;
        case GAME:
            changeScene(new GameInitializer);
            break;
        case GAMEOVER:
            break;
    }
    newScene = NONE;
}

void World::update(Input* input, double delta){
    for(int i = 0; i < objects.size(); i++){
        objects[i]->update(this, input, delta);
        if(objects[i]->getQueueDelete()){
            deleteQueue.push_back(i);
        }
    }
    for(int i = deleteQueue.size()-1; i >= 0; i--){
        int tempDelete = deleteQueue[i];
        delete objects[tempDelete];
        objects.erase(objects.begin() + tempDelete);
    }
    deleteQueue.clear(); //Not sure if this is good because it only deletes objects after they set their bool is true (in their update)
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

MainMenuInitializer::~MainMenuInitializer(){
    delete startGameObserver;
    delete openInfoObserver;
    delete quitObserver;
}

void MainMenuInitializer::initialize(World* world){
    quitObserver = new QuitObserver(world);

    Button* startButton = new Button(sf::Vector2f(316.5, 325.0));
    startGameObserver = new StartGameObserver(world);
    startButton->addObserver(startGameObserver);
    startButton->setOutsideSprite("assets/Menu/Play.png");
    startButton->setInsideSprite("assets/Menu/Safe.png");

    Button* infoButton = new Button(sf::Vector2f(316.5, 450.0));
    openInfoObserver = new OpenInfoObserver(world);
    infoButton->addObserver(openInfoObserver);
    infoButton->setOutsideSprite("assets/Menu/Info.png");
    infoButton->setInsideSprite("assets/Menu/Safe.png");

    world->addObject(startButton);
    world->addObject(infoButton);
}

InfoInitializer::~InfoInitializer(){
    delete toMainObserver;
}

void InfoInitializer::initialize(World* world){
    Button* backButton = new Button(sf::Vector2f(50.0, 475.0));
    toMainObserver = new ToMainObserver(world);
    backButton->addObserver(toMainObserver);
    backButton->setOutsideSprite("assets/Menu/Back.png");
    backButton->setInsideSprite("assets/Menu/Safe.png");
    world->addObject(backButton);
}


//pg.Vector2(100, 500), pg.Vector2(200, 500), pg.Vector2(100, 400), pg.Vector2(200, 400)