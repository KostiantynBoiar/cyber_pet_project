//
// Created by kostiantyn on 11/3/23.
//

#include "../headers/Game.h"

Game::Game() {

}

Game::~Game() {
    delete this->window;
}

void Game::update() {

}

void Game::render() {

}

void Game::initializeVariables() {
    this->window = nullptr;

}

void Game::initWindow() {
    this->videoMode.height = 720;
    this->videoMode.width = 1280;
    this->window = new sf::RenderWindow(this->videoMode, "Cyber pet game");
}
