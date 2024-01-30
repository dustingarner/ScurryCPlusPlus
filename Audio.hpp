#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <string>
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"
#include "Observer.hpp"

using std::string;

class SoundBufferManager{
    public:
    SoundBufferManager();
    void playSound(string fileName);

    private:
    sf::SoundBuffer menuClickBuffer;
    sf::Sound menuClickSound;
    sf::SoundBuffer capture1Buffer;
    sf::Sound capture1Sound;
    sf::SoundBuffer capture2Buffer;
    sf::Sound capture2Sound;
    sf::SoundBuffer capture3Buffer;
    sf::Sound capture3Sound;
    sf::SoundBuffer safe1Buffer;
    sf::Sound safe1Sound;
    sf::SoundBuffer safe2Buffer;
    sf::Sound safe2Sound;
    sf::SoundBuffer safe3Buffer;
    sf::Sound safe3Sound;
    sf::SoundBuffer safe4Buffer;
    sf::Sound safe4Sound;
    sf::SoundBuffer safe5Buffer;
    sf::Sound safe5Sound;
};

class SoundPlayer{
    public:
    SoundPlayer();
    ~SoundPlayer();
    void playMenuClick() {bufferManager.playSound("assets/Sounds/Click.mp3");}
    void playCaptureSound();
    void playSafeSound();
    void playSound(string fileName);

    Observer* getMenuClickObserver() {return menuClickObserver;}
    Observer* getCaptureObserver() {return captureObserver;}
    Observer* getSafeObserver() {return safeObserver;}

    private:
    Observer* menuClickObserver;
    Observer* captureObserver;
    Observer* safeObserver;
    SoundBufferManager bufferManager = SoundBufferManager();
};

class PlayMenuClickObserver : public Observer{
    public:
    PlayMenuClickObserver(SoundPlayer* _soundPlayer) : soundPlayer(_soundPlayer) {}
    virtual ~PlayMenuClickObserver() {}
    virtual void execute(GameObject& object) {soundPlayer->playMenuClick();}

    private:
    SoundPlayer* soundPlayer;
};

class PlayCaptureSoundObserver : public Observer{
    public:
    PlayCaptureSoundObserver(SoundPlayer* _soundPlayer) : soundPlayer(_soundPlayer) {}
    virtual ~PlayCaptureSoundObserver() {}
    virtual void execute(GameObject& object) {soundPlayer->playCaptureSound();}

    private:
    SoundPlayer* soundPlayer;
};

class PlaySafeSoundObserver : public Observer{
    public:
    PlaySafeSoundObserver(SoundPlayer* _soundPlayer) : soundPlayer(_soundPlayer) {}
    virtual ~PlaySafeSoundObserver() {}
    virtual void execute(GameObject& object) {soundPlayer->playSafeSound();}

    private:
    SoundPlayer* soundPlayer;
};


class MusicPlayer{
    public:
    MusicPlayer();
    ~MusicPlayer();
    void playSong();
    void playCongrats();
    void playEnd();

    Observer* getSongObserver() {return songObserver;}
    Observer* getCongratsObserver() {return congratsObserver;}
    Observer* getEndObserver() {return endObserver;}

    private:
    sf::SoundBuffer songBuffer;
    sf::SoundBuffer congratsBuffer;
    sf::SoundBuffer endBuffer;
    sf::Sound currentSong;
    Observer* songObserver;
    Observer* congratsObserver;
    Observer* endObserver;
};

class SongObserver : public Observer{
    public:
    SongObserver(MusicPlayer* _musicPlayer) : musicPlayer(_musicPlayer) {}
    virtual ~SongObserver() {}
    virtual void execute(GameObject& object) {musicPlayer->playSong();}

    private:
    MusicPlayer* musicPlayer;
};

class CongratsObserver : public Observer{
    public:
    CongratsObserver(MusicPlayer* _musicPlayer) : musicPlayer(_musicPlayer) {}
    virtual ~CongratsObserver() {}
    virtual void execute(GameObject& object) {musicPlayer->playCongrats();}

    private:
    MusicPlayer* musicPlayer;
};

class EndObserver : public Observer{
    public:
    EndObserver(MusicPlayer* _musicPlayer) : musicPlayer(_musicPlayer) {}
    virtual ~EndObserver() {}
    virtual void execute(GameObject& object) {musicPlayer->playEnd();}

    private:
    MusicPlayer* musicPlayer;
};

#endif