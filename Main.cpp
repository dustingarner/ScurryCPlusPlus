#include <iostream>
#include <chrono>
#include "SFML/Graphics.hpp"
#include "Input.hpp"
#include "World.hpp"


void changeScene(World* world, WorldInitializer* initializer){
    world->changeScene(initializer);
    world->initialize();
}

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");

    SpriteObject background = SpriteObject(
        sf::Vector2f(0.0,0.0), "assets/Background.png",
        sf::Vector2f(0.0,0.0), 1.0
    );
    background.initialize();

    //World* world = new World(new TestInitializer());
    World* world = new World(new MainMenuInitializer());
    world->initialize();

    Input* currentInput = new Input();
    currentInput->initialize(&window);

    double accumulator = 0.0;
    const double maxDelta = 1.0 / 60.0;
    auto currentTime = std::chrono::system_clock::now();

    while(window.isOpen()){
        auto newTime = std::chrono::system_clock::now();
        std::chrono::duration<double> delta = newTime - currentTime;
        accumulator += delta.count();
        currentTime = newTime;

        bool prevClicked = currentInput->getMouseClicked();
        delete currentInput;
        currentInput = new Input(prevClicked);

        currentInput->initialize(&window);

        window.clear();
        background.draw(&window);
        //window.display();

        world->update(currentInput, delta.count());
        world->draw(&window); //Maybe change accumulation and whatnot, pass in vector interpolation
        world->attemptSceneChange();
         
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                delete currentInput;
                delete world;
                window.close();
            }
        }
    }

    return 0;
}

