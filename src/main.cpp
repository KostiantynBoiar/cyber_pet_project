#include <SFML/Graphics.hpp>
#include <caca_conio.h>
#include "headers/Game.h"

int main()
{
    /*That's window properties of my game*/
    Game game;
    while (game.getWindowIsOpen())
    {
        game.update();
        game.render();

    }

    return 0;
}