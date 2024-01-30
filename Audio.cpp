#include "Audio.hpp"


SoundBufferManager::SoundBufferManager(){
    menuClickBuffer.loadFromFile("assets/Sounds/Click.mp3");
    menuClickSound.setBuffer(menuClickBuffer);
    capture1Buffer.loadFromFile("assets/Sounds/Aaahhgghhh.mp3");
    capture1Sound.setBuffer(capture1Buffer);
    capture2Buffer.loadFromFile("assets/Sounds/Nooo.mp3");
    capture2Sound.setBuffer(capture2Buffer);
    capture3Buffer.loadFromFile("assets/Sounds/Oof.mp3");
    capture3Sound.setBuffer(capture3Buffer);
    safe1Buffer.loadFromFile("assets/Sounds/Hooray.mp3");
    safe1Sound.setBuffer(safe1Buffer);
    safe2Buffer.loadFromFile("assets/Sounds/Thanks.mp3");
    safe2Sound.setBuffer(safe2Buffer);
    safe3Buffer.loadFromFile("assets/Sounds/Yay I didn't die.mp3");
    safe3Sound.setBuffer(safe3Buffer);
    safe4Buffer.loadFromFile("assets/Sounds/Yayy.mp3");
    safe4Sound.setBuffer(safe4Buffer);
    safe5Buffer.loadFromFile("assets/Sounds/Yippee.mp3");
    safe5Sound.setBuffer(safe5Buffer);
}

void SoundBufferManager::playSound(string fileName){
    if(fileName == "assets/Sounds/Click.mp3") {menuClickSound.play();}
    if(fileName == "assets/Sounds/Aaahhgghhh.mp3") {capture1Sound.play();}
    if(fileName == "assets/Sounds/Nooo.mp3") {capture2Sound.play();}
    if(fileName == "assets/Sounds/Oof.mp3") {capture3Sound.play();}
    if(fileName == "assets/Sounds/Hooray.mp3") {safe1Sound.play();}
    if(fileName == "assets/Sounds/Thanks.mp3") {safe2Sound.play();}
    if(fileName == "assets/Sounds/Yay I didn't die.mp3") {safe3Sound.play();}
    if(fileName == "assets/Sounds/Yayy.mp3") {safe4Sound.play();}
    if(fileName == "assets/Sounds/Yippee.mp3") {safe5Sound.play();}
}


SoundPlayer::SoundPlayer(){
    menuClickObserver = new PlayMenuClickObserver(this);
    captureObserver = new PlayCaptureSoundObserver(this);
    safeObserver = new PlaySafeSoundObserver(this);
}

SoundPlayer::~SoundPlayer(){
    delete menuClickObserver;
    delete captureObserver;
    delete safeObserver;
}


void SoundPlayer::playCaptureSound(){
    int randFile = rand() % 3;
    switch(randFile){
        case 0:
            bufferManager.playSound("assets/Sounds/Aaahhgghhh.mp3");
            break;
        case 1:
            bufferManager.playSound("assets/Sounds/Nooo.mp3");
            break;
        case 2:
            bufferManager.playSound("assets/Sounds/Oof.mp3");
            break;
    }
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
    bufferManager.playSound(filePath);
}


MusicPlayer::MusicPlayer(){
    songBuffer.loadFromFile("assets/Music/Song.mp3");
    congratsBuffer.loadFromFile("assets/Music/Congrats.mp3");
    endBuffer.loadFromFile("assets/Music/End.mp3");
    songObserver = new SongObserver(this);
    congratsObserver = new CongratsObserver(this);
    endObserver = new EndObserver(this);
}

MusicPlayer::~MusicPlayer(){
    delete songObserver;
    delete congratsObserver;
    delete endObserver;
}

void MusicPlayer::playSong(){
    if(currentSong.getBuffer() == &songBuffer){
        return;
    }
    currentSong.stop();
    currentSong.setBuffer(songBuffer);
    currentSong.play();
}

void MusicPlayer::playCongrats(){
    currentSong.stop();
    currentSong.setBuffer(congratsBuffer);
    currentSong.play();
}

void MusicPlayer::playEnd(){
    currentSong.stop();
    currentSong.setBuffer(endBuffer);
    currentSong.play();
}


