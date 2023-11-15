//
// Created by kostiantyn on 11/3/23.
//

#ifndef CYBER_PET_PROJECT_GAME_H
#define CYBER_PET_PROJECT_GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Player.h"
#include "Button.h"
#include "JSON_API.h"
#include <iostream>
#include <SFML/Graphics/Text.hpp>
#include "Button.h"

/*Header of class that acts the game engine*/

class Game {

private:

    sf::RenderWindow* window;
    sf::Event event;
    sf::VideoMode videoMode;
    sf::Font font;

    void initVariables();
    void initWindow();

    Player* player;

    std::vector<Button> buttons;
public:

    Game();
    virtual ~Game();

    void update();
    void render();
    const bool getWindowIsOpen() const;

    void initPlayer();
    void pollEvents();

    void renderPlayer();
    void updatePlayer();
    static sf::Font getFont();

    void createButtons();
    void renderButtons();
};


#endif //CYBER_PET_PROJECT_GAME_H
