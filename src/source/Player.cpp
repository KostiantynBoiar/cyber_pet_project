//
// Created by Kostiantyn on 11/3/23.
// That's class with realization methods of our player
//

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

Player::Player(std::string playerName) {
    this->initSprite();
    this->initTexture();
    this->playerName = playerName;
}

Player::~Player() {

}

void Player::playerState() {

}

void Player::initSprite() {

}

void Player::initTexture() {

}

void Player::update() {

}

void Player::render(sf::RenderTarget &target) {

}

