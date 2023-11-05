#include <iostream>
#include "../headers/Game.h"

Game::Game() {
    this->initVariables();
    this->initPlayer();
    this->initWindow();
}

Game::~Game() {
    delete this->window;
    delete this->player;
}

void Game::update() {
    this->pollEvents();
    this->updatePlayer();
}

void Game::render() {
    this->window->clear();

    // Draw game objects
    this->renderPlayer();

    this->window->display();
}

void Game::initVariables() {
    this->window = nullptr;
}

void Game::initWindow() {
    this->videoMode.height = 720;
    this->videoMode.width = 1280;
    this->window = new sf::RenderWindow(this->videoMode, "Cyber pet game");
}

const bool Game::getWindowIsOpen() const {
    return this->window->isOpen();
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->event)) {
        switch (this->event.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
        }
    }
}

void Game::renderPlayer() {
    this->player->render(*this->window);
}

void Game::initPlayer() {
    this->player = new Player();
}

void Game::updatePlayer() {
    this->player->update();
}
