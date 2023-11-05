#include <SFML/Graphics.hpp>
#include "source/Game.cpp" /*Here is must be cpp file instead of .h*/
#include "source/Player.cpp"
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