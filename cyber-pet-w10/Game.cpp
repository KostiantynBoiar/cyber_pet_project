#include "Game.h"

JSON_API jsonApi("gameFile.json");
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
    this->renderButtons();
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
        case sf::Event::MouseButtonPressed:
            for (Button& button : buttons) {
                if (button.isClicked(*this->window, this->event)) {
                    // Handle button click here
                    if (button.getText() == "Feed") {
                        jsonApi.getActualDate();
                        jsonApi.updateFoodTime();
                        player->setPlayerHP(100);
                        player->setHungryLevel();
                        std::cout << "Feed button clicked" << std::endl;
                    }
                    else if (button.getText() == "Rest") {
                        std::cout << "Rest button clicked" << std::endl;
                        jsonApi.updateRestTime();
                        player->setPlayerHP(100);
                        player->setRestLevel();
                        
                    }
                }
            }
            break;
        }
    }
}


void Game::renderPlayer() {
    this->player->render(*this->window);
    if (!font.loadFromFile("Raleway-Bold.ttf")) {
        std::cout << "Font could not be found";
    }
    else {
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
        if (playerHP < 0) {

            std::cout << "Player has die";

            sf::Text dieText;
            dieText.setFont(font);

            hpText.setFillColor(sf::Color::Black);
            std::string dieString = "Player has die";
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
    createButtons();
}

void Game::updatePlayer() {
    this->player->update();
}

void Game::createButtons() {
    if (!font.loadFromFile("Raleway-Bold.ttf")) {
        std::cout << "Font could not be found";
    }
    else {
        Button feedButton(50, 50, 100, 40, font, "Feed");
        Button restButton(200, 50, 100, 40, font, "Rest");

        buttons.push_back(feedButton);
        buttons.push_back(restButton);
    }
}

void Game::renderButtons() {
    for (const Button& button : buttons) {
        button.render(*this->window);
    }
}