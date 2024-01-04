#ifndef COMMAND_H
#define COMMAND_H
#include "GameObject.hpp"

class Command{
    public:
    virtual ~Command();
    virtual void execute(const GameObject& gameObject) = 0;
};

class StartGameCommand : Command{
    public:
    virtual void execute(const GameObject& gameObject);
};

class ShowInfoCommand : Command{
    public:
    virtual void execute(const GameObject& gameObject);
};


#endif