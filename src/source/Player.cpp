#include <iostream>
#include "../headers/Player.h"
#define xPos 330
#define yPos 290

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
    this->sprite.setPosition(sf::Vector2f(xPos, yPos));
    target.draw(this->sprite);
}
