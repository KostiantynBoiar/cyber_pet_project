#include <iostream>
#include "../headers/Player.h"
#include <chrono>
#include <thread>
#define xPos 330
#define yPos 290


static std::string pathToTextures[] = {"/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/textures/png/Idle (1).png",
                                       "/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/textures/png/Idle (2).png",
                                       "/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/textures/png/Idle (3).png",
                                       "/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/textures/png/Idle (4).png",
                                       "/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/textures/png/Idle (5).png",
                                       "/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/textures/png/Idle (6).png",
                                       "/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/textures/png/Idle (7).png",
                                       "/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/textures/png/Idle (8).png",
                                       "/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/textures/png/Idle (9).png",
                                       "/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/textures/png/Idle (10).png"};


int Player::getPlayerHP() {
    return playerHP;
}

void Player::setPlayerHP(int playerHP) {
    this->playerHP = playerHP;
}

Player::Player() {
    this->initSprite();
    this->initTexture();
    this->setPlayerHP(100); // Initialize HP to a default value
    this->updateCounter = 0;
    this->hungryLevel = wellFed;
    this->sleepLevel = wideAwake;
    this->lastHealthUpdateTime = std::chrono::steady_clock::now();
}

Player::~Player() {

}


void Player::initSprite() {
}

void Player::initTexture() {
    if (!this->texture.loadFromFile(pathToTextures[0])) {
        std::cout << "ERROR: PLAYER TEXTURE COULD NOT LOAD FROM FILE\n";
    }


}
int currentTextureIndex = 0;

void Player::update() {

    updateTexture();

    updateCounter++;
    JSON_API jsonApi("gameFile.json");
    if (updateCounter >= 10) {
        updateHungryLevel(jsonApi.getFoodState());
        updateRestLevel(jsonApi.getRestState());
        //updateSleep();
        updateHealth();
        lastHealthUpdateTime = std::chrono::steady_clock::now();
        updateCounter = 0;
    }
}

void Player::render(sf::RenderTarget& target) {
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(sf::Vector2f(xPos, yPos));
    target.draw(this->sprite);
}

void Player::updateTexture() {
    currentTextureIndex = (currentTextureIndex + 1) % 7;
    this->texture.loadFromFile(pathToTextures[currentTextureIndex]);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if(this->playerHP < 50){
        this->texture.loadFromFile("/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/textures/png/Dead (1).png");
    }
    if(this->playerHP < 0){
        this->texture.loadFromFile("/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/textures/png/Dead (4).png");
    }
}

void Player::updateHealth() {
    switch (hungryLevel) {
        case wellFed:
            setPlayerHP(getPlayerHP() + 5);
            break;
        case slightlyPeckish:
            setPlayerHP(getPlayerHP() - 2);
            break;
        case ratherHungry:
            setPlayerHP(getPlayerHP() - 5);
            break;
        case starving:
            setPlayerHP(getPlayerHP() - 10);
            break;
        case dead:
            setPlayerHP(0);
            break;
    }
}

void Player::updateSleep() {

    switch (sleepLevel) {
        case wideAwake:
            setPlayerHP(getPlayerHP() + 5);
        case awake:
            setPlayerHP(getPlayerHP() + 0);
        case tired:
            setPlayerHP(getPlayerHP() - 1);
        case failingAsleep:
            setPlayerHP(getPlayerHP() - 4);
        case collapsed:
            setPlayerHP(getPlayerHP() - 10);
    }
}

void Player::updateHungryLevel(int foodState) {
    switch (foodState) {
        case 1:
            hungryLevel = wellFed;
            break;
        case 2:
            hungryLevel = slightlyPeckish;
            break;
        case 3:
            hungryLevel = ratherHungry;
            break;
        case 4:
            hungryLevel = starving;
            break;
        case 5:
            hungryLevel = starving;
            break;
    }
}

void Player::setHungryLevel() {
    this->hungryLevel = wellFed;
}

void Player::updateRestLevel(int restState) {
    switch(restState){
        case 1:
            sleepLevel = wideAwake;
        case 2:
            sleepLevel = awake;
        case 3:
            sleepLevel = tired;
        case 4:
            sleepLevel = failingAsleep;
        case 5:
            sleepLevel = collapsed;
    }
}

void Player::setRestLevel() {
    this->sleepLevel = wideAwake;
}

