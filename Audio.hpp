#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include "Observer.hpp"

using std::string;

typedef void (*Func)();

class PlaySoundObserver : public Observer{
    public:
    PlaySoundObserver(Func _func) : func(_func) {}
    virtual ~PlaySoundObserver() {}
    virtual void execute(GameObject& object) {func();}

    private:
    Func func;
};

class SoundPlayer{
    public:
    SoundPlayer();
    ~SoundPlayer();
    void playMenuClick() {} //play sound
    void playCaptureSound();
    void playSafeSound();
    Observer* getMenuClickObserver() {return menuClickObserver;}
    Observer* getCaptureObserver() {return captureObserver;}
    Observer* getSafeObserver() {return safeObserver;}

    private:
    Observer* menuClickObserver;
    Observer* captureObserver;
    Observer* safeObserver;
};

class MusicPlayer{

};


#endif