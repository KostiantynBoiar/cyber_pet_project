//
// Created by Kostiantyn on 11/3/23.
// That's class with realization methods of our player
//

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
}

int Player::setPlayerHP(int playerHP) {
    this->playerHP = playerHP;
}

int Player::getPlayerAge() {
    return playerAge;
}

int Player::setPlayerAge(int playerAge) {
    this->playerAge = playerAge;
}

Player::Player() {
    this->initSprite();
    this->initTexture();
}

Player::~Player() {

}

void Player::playerState() {

}

void Player::initSprite() {
    this->sprite.setTexture(this->texture);
}

void Player::initTexture() {
    if(!this->texture.loadFromFile("src/assets/textures/png/Idle (1).png")){
        std::cout << "ERROR: PLAYER COULD NOT LOAD FROM FILE\n";
    }
}

void Player::update() {

}

void Player::render(sf::RenderTarget& target) {

}

