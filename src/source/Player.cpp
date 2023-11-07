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

std::string Player::getPlayerName() {
    return playerName;
}

std::string Player::setPlayerName(std::string playerName) {
    this->playerName = playerName;
    return playerName;
}

void Player::setPlayerHP(int playerHP) {
    this->playerHP = playerHP;
}

int Player::getPlayerAge() {
    return playerAge;
}

int Player::setPlayerAge(int playerAge) {
    this->playerAge = playerAge;
    return playerAge;
}

Player::Player() {
    this->initSprite();
    this->initTexture();
    this->setPlayerHP(100); // Initialize HP to a default value
    this->hungryLevel = starving;
}

Player::~Player() {

}

void Player::playerState() {
    // Implement the playerState method if needed
}

void Player::initSprite() {
    // Initialize the sprite if necessary
}

void Player::initTexture() {
        if (!this->texture.loadFromFile(pathToTextures[0])) {
            std::cout << "ERROR: PLAYER TEXTURE COULD NOT LOAD FROM FILE\n";
    }


}
int currentTextureIndex = 0;

void Player::update() {
    updateTexture();
    updateHealth();
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

