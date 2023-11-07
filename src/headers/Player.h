// Player.h
#ifndef CYBER_PET_PROJECT_PLAYER_H
#define CYBER_PET_PROJECT_PLAYER_H

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

class Player {

private:
    sf::Sprite sprite;
    sf::Texture texture;

    std::string playerName;
    int playerHP;
    int playerAge;

    void initSprite();
    void initTexture();

    enum HungryLevel {
        wellFed,
        slightlyPeckish,
        ratherHungry,
        starving,
        dead
    };
    HungryLevel hungryLevel;
public:
    Player();
    virtual ~Player();

    std::string getPlayerName();
    std::string setPlayerName(std::string playerName);

    int getPlayerHP();
    void setPlayerHP(int playerHP); // Changed return type to void

    int getPlayerAge();
    int setPlayerAge(int playerAge);

    void updateTexture();
    void playerState();

    void update();
    void render(sf::RenderTarget& target);
    void updateHealth();
};

#endif //CYBER_PET_PROJECT_PLAYER_H
