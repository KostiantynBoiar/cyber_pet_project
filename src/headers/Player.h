//
// Created by kostiantyn on 11/3/23.
//

#ifndef CYBER_PET_PROJECT_PLAYER_H
#define CYBER_PET_PROJECT_PLAYER_H

#include <string>

class Player {

private:
    std::string playerName;
    int playerHP;
    int playerAge;

public:
  Player(std::string playerName);
  virtual ~Player();
  std::string getPlayerName();
  std::string setPlayerName(std::string playerName);
  int getPlayerHP();
  int setPlayerHP(int playerHP);
  int getPlayerAge();
  int setPlayerAge(int playerAge);

};


#endif //CYBER_PET_PROJECT_PLAYER_H
