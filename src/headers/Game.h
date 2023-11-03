//
// Created by kostiantyn on 11/3/23.
//

#ifndef CYBER_PET_PROJECT_GAME_H
#define CYBER_PET_PROJECT_GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

/*Header of class that acts the game engine*/

class Game {
private:
    sf::RenderWindow* window;
    sf::Event event;
    sf::VideoMode videoMode;
    void initializeVariables();
    void initWindow();
public:
    Game();
    virtual ~Game();
    void update();
    void render();
    const bool getWindowIsOpen() const;
};


#endif //CYBER_PET_PROJECT_GAME_H
