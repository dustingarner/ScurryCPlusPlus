#include "Audio.hpp"


SoundPlayer::SoundPlayer(){
    menuClickObserver = new PlaySoundObserver([this](){playMenuClick;});
    captureObserver = new PlaySoundObserver([this](){playCaptureSound;});
    safeObserver = new PlaySoundObserver([this](){playSafeSound;});
}

SoundPlayer::~SoundPlayer(){
    delete menuClickObserver;
    delete captureObserver;
    delete safeObserver;
}


#include <iostream>
void SoundPlayer::playCaptureSound(){
    string filePath;
    int randFile = rand() % 3;
    switch(randFile){
        case 0:
            filePath = "assets/Sounds/Aaahhgghhh.mp3";
            break;
        case 1:
            filePath = "assets/Sounds/Nooo.mp3";
            break;
        case 2:
            filePath = "assets/Sounds/Oof.mp3";
            break;
    }
    std::cout << "dead" << std::endl;
    //play file
}

void SoundPlayer::playSafeSound(){
    string filePath;
    int randFile = rand() % 5;
    switch(randFile){
        case 0:
            filePath = "assets/Sounds/Hooray.mp3";
            break;
        case 1:
            filePath = "assets/Sounds/Thanks.mp3";
            break;
        case 2:
            filePath = "assets/Sounds/Yay I didn't die.mp3";
            break;
        case 3:
            filePath = "assets/Sounds/Yayy.mp3";
            break;
        case 4:
            filePath = "assets/Sounds/Yippee.mp3";
            break;
    }
    std::cout << "safe!" << std::endl;
    //Play sound
}


