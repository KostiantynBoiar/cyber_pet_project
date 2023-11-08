//
// Created by kostiantyn on 11/7/23.
//

#include <SFML/Window/Mouse.hpp>
#include "../headers/Button.h"

Button::Button(float x, float y, float width, float height, sf::Font &font, std::string text) {
    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Green);

    this->text.setFont(font);
    this->text.setString(text);
    this->text.setCharacterSize(24);
    this->text.setFillColor(sf::Color::White);
    this->text.setPosition(x + 10, y + 10);
}

bool Button::isMouseOver(const sf::RenderWindow &window) const {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f buttonPosition = shape.getPosition();
    sf::Vector2f buttonSize = shape.getSize();

    return mousePosition.x >= buttonPosition.x && mousePosition.x <= buttonPosition.x + buttonSize.x &&
           mousePosition.y >= buttonPosition.y && mousePosition.y <= buttonPosition.y + buttonSize.y;
}

void Button::render(sf::RenderWindow &window) const {
    window.draw(shape);
    window.draw(text);
}
