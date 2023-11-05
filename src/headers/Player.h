//
// Created by kostiantyn on 11/3/23.
//

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

public:

  Player();
  virtual ~Player();

  std::string getPlayerName();
  std::string setPlayerName(std::string playerName);
  int getPlayerHP();
  int setPlayerHP(int playerHP);
  int getPlayerAge();
  int setPlayerAge(int playerAge);

  void playerState();
  void update();
  void render(sf::RenderTarget& target);
};


#endif //CYBER_PET_PROJECT_PLAYER_H
