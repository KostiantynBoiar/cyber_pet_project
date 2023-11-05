#include <iostream>
#include "../headers/Player.h"

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

int Player::setPlayerHP(int playerHP) {
    this->playerHP = playerHP;
    return playerHP;
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
    if (!this->texture.loadFromFile("/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/textures/png/Idle (6).png")) {
        std::cout << "ERROR: PLAYER COULD NOT LOAD FROM FILE\n";
    }
}

void Player::update() {
    // Implement the update method if needed
}

void Player::render(sf::RenderTarget& target) {
    this->sprite.setTexture(this->texture);
    target.draw(this->sprite);
}
