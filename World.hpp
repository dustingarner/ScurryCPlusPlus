#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Input.hpp"
#include "Observer.hpp"
#include "GameObject.hpp"
#include "Menu.hpp"
#include "Mouse.hpp"
#include "Enemy.hpp"
#include "Shelter.hpp"

using std::vector;

class World;
class EnemySpawnObserver;


enum sceneType {NONE, MAIN, INFO, GAME, GAMEOVER};

class WorldInitializer{
    public:
    virtual ~WorldInitializer() {}
    virtual void initialize(World* world) = 0;
};

class MainMenuInitializer : public WorldInitializer{
    public:
    virtual ~MainMenuInitializer();
    virtual void initialize(World* world);

    private:
    Observer* startGameObserver;
    Observer* openInfoObserver;
    Observer* quitObserver;
};

class InfoInitializer : public WorldInitializer{
    public:
    virtual ~InfoInitializer();
    virtual void initialize(World* world);

    private:
    Observer* toMainObserver;
};

class GameInitializer : public WorldInitializer{
    public:
    virtual ~GameInitializer();
    virtual void initialize(World* world);
    void uncontrolMice();
    void removeMouse(GameObject& mouse);
    int getScore() {return score;}
    void endGame();

    private:
    EnemySpawnerObject* spawner;
    EnemySpawnObserver* spawnObserver;
    Observer* mouseClickObserver;
    vector<MouseObject*> allMice;
    Observer* mouseRemoveObserver;
    Observer* gameEndObserver;
    int score = 0;
};

class TestInitializer : public WorldInitializer{
    public:
    virtual void initialize(World* world);
};


class EnemySpawnObserver : public Observer{
    public:
    EnemySpawnObserver(World* _world, const vector<MouseObject*>& _allMice, Observer* _mouseRemoveObserver) 
            : world(_world), allMice(_allMice), mouseRemoveObserver(_mouseRemoveObserver) {}
    virtual ~EnemySpawnObserver() {}
    virtual void execute(GameObject& object);

    private:
    World* world;
    const vector<MouseObject*>& allMice;
    Observer* mouseRemoveObserver;
};

class MouseClickObserver : public Observer{
    public:
    MouseClickObserver(GameInitializer* _gameInitializer) : gameInitializer(_gameInitializer) {}
    virtual ~MouseClickObserver() {}
    virtual void execute(GameObject& object) {gameInitializer->uncontrolMice();}

    private:
    GameInitializer* gameInitializer;
};

class MouseRemoveObserver : public Observer{
    public:
    MouseRemoveObserver(GameInitializer* _gameInitializer) : gameInitializer(_gameInitializer) {}
    virtual ~MouseRemoveObserver() {}
    virtual void execute(GameObject& object) {gameInitializer->removeMouse(object);}

    private:
    GameInitializer* gameInitializer;
};

class GameEndObserver : public Observer{
    public:
    GameEndObserver(GameInitializer* _gameInitializer, World* _world) : 
            gameInitializer(_gameInitializer), world(_world) {}
    virtual ~GameEndObserver() {}
    virtual void execute(GameObject& object);

    private:
    GameInitializer* gameInitializer;
    World* world;
};

class GameOverInitializer : public WorldInitializer{
    public:
    GameOverInitializer(int _score) : score(_score) {}
    virtual ~GameOverInitializer() {}
    virtual void initialize(World* world);

    private:
    int score;
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
    void quitGame() {}
    void clearObjects();
    void attemptSceneChange();
    void setNewScene(sceneType _newScene) {newScene = _newScene;}
    void setScore(int score) {currentScore = score;}

    private:
    vector<Observer*> observers;
    vector<GameObject*> objects;
    vector<int> deleteQueue;
    WorldInitializer* worldInitializer;
    sceneType newScene = NONE;
    short int currentScore = 0;
};


class StartGameObserver : public Observer{
    public:
    StartGameObserver(World* _world) : world(_world) {}
    virtual ~StartGameObserver() {}
    virtual void execute(GameObject& object) {world->setNewScene(GAME);}

    private:
    World* world;
};

class OpenInfoObserver : public Observer{
    public:
    OpenInfoObserver(World* _world) : world(_world) {}
    virtual ~OpenInfoObserver() {}
    virtual void execute(GameObject& object) {world->setNewScene(INFO);}

    private:
    World* world;
};

class QuitObserver : public Observer{
    public:
    QuitObserver(World* _world) : world(_world) {}
    virtual ~QuitObserver() {}
    virtual void execute(GameObject& object) {world->quitGame();}

    private:
    World* world;
};

class ToMainObserver : public Observer{
    public:
    ToMainObserver(World* _world) : world(_world) {}
    virtual ~ToMainObserver() {}
    virtual void execute(GameObject& object) {world->setNewScene(MAIN);}

    private:
    World* world;
};


#endif