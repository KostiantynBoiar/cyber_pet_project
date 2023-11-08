#include <iostream>
#include <SFML/Graphics/Text.hpp>
#include "../headers/Game.h"
#include "../headers/Button.h"

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
    sf::Font font;

    if(!font.loadFromFile("/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/fonts/Raleway-Bold.ttf")){
        std::cout << "Font could not be found";
    }else {
        sf::Text hpText;
        hpText.setFont(font); // Set the font for the text
        hpText.setCharacterSize(20);
        hpText.setFillColor(sf::Color::White);
        hpText.setPosition(10, 10); // Set the position of the text on the screen

        // Convert player's HP to a string and set it as the text
        int playerHP = this->player->getPlayerHP();
        std::string hpString = "HP: " + std::to_string(playerHP);
        hpText.setString(hpString);

        // Draw the HP text on the screen
        this->window->draw(hpText);


        /*
         * If PlayerHP < 0 then we will clean previous text and replace it on some kinda "Player has die"
         * */
        if(playerHP < 0){

            std::cout << "Player has die";

            sf::Text dieText;
            dieText.setFont(font);

            hpText.setFillColor(sf::Color::Black);
            std::string dieString = "Player has die ebat' ti lox";
            dieText.setCharacterSize(20);

            dieText.setFillColor(sf::Color::White);
            dieText.setPosition(10, 10);
            dieText.setString(dieString);

            this->window->draw(hpText);
            this->window->draw(dieText);
        }

    }

}

void Game::initPlayer() {
    this->player = new Player();
}

void Game::updatePlayer() {
    this->player->update();
}
/* If I try to implement draw player's hp through a function I got error message "segmentation fault"
sf::Font Game::getFont() {
    sf::Font font;
    if(!font.loadFromFile("/home/kostiantyn/Documents/education/C/cyber-pet-project/src/assets/fonts/Raleway-Bold.ttf")){
        std::cout << "Font could not be found";
    }
    return font;
}
*/