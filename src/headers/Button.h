//
// Created by kostiantyn on 11/7/23.
//

#ifndef CYBER_PET_PROJECT_BUTTON_H
#define CYBER_PET_PROJECT_BUTTON_H
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
public:
    Button(float x, float y, float width, float height, sf::Font& font, std::string text);

    bool isMouseOver(const sf::RenderWindow& window) const;
    bool isClicked(const sf::RenderWindow& window, sf::Event event);

    void render(sf::RenderWindow& window) const;

    std::string getText() const;
};


#endif //CYBER_PET_PROJECT_BUTTON_H
