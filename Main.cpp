#include <iostream>
#include <chrono>
#include "SFML/Graphics.hpp"
#include "Input.hpp"

class State{
    public:
    State(){}
    State(Input input){}
};

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");
    sf::RectangleShape shape(sf::Vector2f(200, 100));
    shape.setFillColor(sf::Color::Red);

    Input* currentInput = new Input();
    currentInput->init();

    double accumulator = 0.0;
    const double maxDelta = 1.0 / 60.0;
    auto currentTime = std::chrono::system_clock::now();

    State* prevState;
    State* currentState = new State();

    while(window.isOpen()){
        auto newTime = std::chrono::system_clock::now();
        std::chrono::duration<double> delta = newTime - currentTime;
        accumulator += delta.count();
        currentTime = newTime;

        

        bool prevClicked = currentInput->getMouseClicked();
        delete currentInput;
        currentInput = new Input(prevClicked);
        currentInput->init();

        if(prevState != nullptr){
            delete prevState;
        }
        prevState = currentState;
        currentState = new State(currentInput);




        /*
        sf::Vector2f moveAxes(0,0);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            moveAxes.x -= 1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            moveAxes.x += 1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            moveAxes.y -= 1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            moveAxes.y += 1;
        }

        if(abs(moveAxes.x) + abs(moveAxes.y) > 1){
            moveAxes.x *= sqrt(1.0/2.0);
            moveAxes.y *= sqrt(1.0/2.0);
        }

        shape.setPosition(shape.getPosition() + (moveAxes * SPEED));
        */


        window.clear();
        window.draw(shape); //Rendering stuff here
        window.display();



        //sf::Vector2u a(800, 600 + (counter % 200));
        //window.setSize(a);

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                delete currentInput;
                delete prevState;
                delete currentState;
                window.close();
            }
        }

    }

    return 0;
}


//g++ sfml.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include -o prog -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
