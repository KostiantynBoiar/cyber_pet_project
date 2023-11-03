//
// Created by kostiantyn on 11/3/23.
//

#ifndef CYBER_PET_PROJECT_GAME_H
#define CYBER_PET_PROJECT_GAME_H

/*Header of class that acts the game engine*/

class Game {
private:
    void initializeVariables();
    void initWindow();
public:
    Game();
    virtual ~Game();
    void update();
    void render();

};


#endif //CYBER_PET_PROJECT_GAME_H
