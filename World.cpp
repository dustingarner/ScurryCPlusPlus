#include "World.hpp"

GameInitializer::~GameInitializer(){
    delete spawnObserver;
    delete mouseClickObserver;
    delete mouseRemoveObserver;
    delete gameEndObserver;
    //delete other things
}

void GameInitializer::initialize(World* world){
    gameEndObserver = new GameEndObserver(this, world);
    world->setScore(0);
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
    spawner = new EnemySpawnerObject();
    spawner->connectObserver(spawnObserver);
    spawner->initialize();
    world->addObject(spawner);
    TimerObject* spawnStartTimer = new TimerObject(0.1);
    spawnStartTimer->addObserver(spawner->getTurnOnObserver());
    world->addObject(spawnStartTimer);
    
    Shelter* shelter = new Shelter(allMice); //Make this into a function?
    shelter->initialize();
    shelter->addRemoveObserver(mouseRemoveObserver);
    shelter->addRemoveObserver(world->getSoundPlayer()->getSafeObserver());
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
    gameEndObserver->execute(*spawner);
}

void EnemySpawnObserver::execute(GameObject& object){
    EnemyObject* newEnemy = spawnEnemy(allMice, mouseRemoveObserver);
    newEnemy->addCaptureObserver(world->getSoundPlayer()->getCaptureObserver());
    world->addObject(newEnemy);
}

void GameEndObserver::execute(GameObject& object){
    int score = gameInitializer->getScore();
    world->setScore(score);
    world->setNewScene(GAMEOVER);
}

void GameOverInitializer::initialize(World* world){
    TimerObject* timer;
    if(score == 4){
        SpriteObject* congratsSprite = new SpriteObject(
            sf::Vector2f(90.0,200.0), "assets/Menu/Congratulations.png", 
            sf::Vector2f(0.0,0.0), 0.6
        );
        congratsSprite->initialize();
        world->addObject(congratsSprite);
        world->notifyPerfectEnd(*congratsSprite);
        timer = new TimerObject(5);
    }
    else{
        SpriteObject* casualtiesTextSprite = new SpriteObject(
            sf::Vector2f(150.0,125.0), "assets/Menu/Casualties.png",
            sf::Vector2f(0.0,0.0), 0.5
        );
        casualtiesTextSprite->initialize();
        world->addObject(casualtiesTextSprite);
        SpriteObject* scoreTextSprite = new SpriteObject(
            sf::Vector2f(150.0,325.0), "assets/Menu/Safe.png",
            sf::Vector2f(0.0,0.0), 0.5
        );
        scoreTextSprite->initialize();
        world->addObject(scoreTextSprite);
        string casualtyCountPath = "assets/Menu/Counter/";
        casualtyCountPath += (4-score)+48;
        casualtyCountPath += ".png";
        SpriteObject* casualtyCountSprite = new SpriteObject(
            sf::Vector2f(450.0,125.0), casualtyCountPath,
            sf::Vector2f(0.0,0.0), 0.5
        );
        casualtyCountSprite->initialize();
        world->addObject(casualtyCountSprite);
        string scoreCountPath = "assets/Menu/Counter/";
        scoreCountPath += score+48;
        scoreCountPath += ".png";
        SpriteObject* scoreCountSprite = new SpriteObject(
            sf::Vector2f(450.0,325.0), scoreCountPath,
            sf::Vector2f(0.0,0.0), 0.5
        );
        scoreCountSprite->initialize();
        world->addObject(scoreCountSprite);
        world->notifyEnd(*scoreCountSprite);
        timer = new TimerObject(3);
    }
    toMainObserver = new ToMainObserver(world);
    
    timer->addObserver(toMainObserver);
    world->addObject(timer);
}


World::World(WorldInitializer* _worldInitializer) : worldInitializer(_worldInitializer){
    soundPlayer = new SoundPlayer;
    musicPlayer = new MusicPlayer;
    startingGame.addObserver(musicPlayer->getSongObserver());
    endingGame.addObserver(musicPlayer->getEndObserver());
    endingPerfectGame.addObserver(musicPlayer->getCongratsObserver());
}

World::~World(){
    clearObjects();
    delete soundPlayer;
    delete musicPlayer;
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
            changeScene(new GameOverInitializer(currentScore));
            break;
    }
    newScene = NONE;
}

void World::update(Input* input, double delta){
    for(int i = 0; i < objects.size(); i++){
        objects[i]->update(this, input, delta);
    }
    for(int i = 0; i < objects.size(); i++){
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

    SpriteObject* title = new SpriteObject(
            sf::Vector2f(140.0,40.0), "assets/Menu/Title.png",
            sf::Vector2f(0.0,0.0), 1
        );
    title->initialize();
    world->addObject(title);

    Button* startButton = new Button(sf::Vector2f(316.5, 325.0));
    startGameObserver = new StartGameObserver(world);
    startButton->addObserver(startGameObserver);
    startButton->addObserver(world->getSoundPlayer()->getMenuClickObserver());
    startButton->setOutsideSprite("assets/Menu/Play.png");
    startButton->setInsideSprite("assets/Menu/Safe.png");

    Button* infoButton = new Button(sf::Vector2f(316.5, 450.0));
    openInfoObserver = new OpenInfoObserver(world);
    infoButton->addObserver(openInfoObserver);
    infoButton->addObserver(world->getSoundPlayer()->getMenuClickObserver());
    infoButton->setOutsideSprite("assets/Menu/Info.png");
    infoButton->setInsideSprite("assets/Menu/Safe.png");

    world->addObject(startButton);
    world->addObject(infoButton);

    world->notifyStart(*title);
}

InfoInitializer::~InfoInitializer(){
    delete toMainObserver;
}

void InfoInitializer::initialize(World* world){
    Button* backButton = new Button(sf::Vector2f(50.0, 475.0));
    toMainObserver = new ToMainObserver(world);
    backButton->addObserver(toMainObserver);
    backButton->addObserver(world->getSoundPlayer()->getMenuClickObserver());
    backButton->setOutsideSprite("assets/Menu/Back.png");
    backButton->setInsideSprite("assets/Menu/Safe.png");
    world->addObject(backButton);

    SpriteObject* infoText = new SpriteObject(
            sf::Vector2f(65.0,25.0), "assets/Menu/InfoText.png",
            sf::Vector2f(0.0,0.0), 0.5
        );
    infoText->initialize();
    world->addObject(infoText);
}


//pg.Vector2(100, 500), pg.Vector2(200, 500), pg.Vector2(100, 400), pg.Vector2(200, 400)