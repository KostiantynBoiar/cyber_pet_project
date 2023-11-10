#include <SFML/Graphics.hpp>
#include "source/Game.cpp" /*Here is must be cpp file instead of .h*/
#include "source/Player.cpp"
#include "source/Button.cpp"
#include "source/JSON_API.cpp"
int main()
{
    Game game;
    Player player;
    JSON_API jsonApi("gameFile.json");
    jsonApi.getActualDate();
    std::cout << "Difference: \n" << jsonApi.getFoodState();
    while (game.getWindowIsOpen())
    {
        game.update();
        player.update();
        game.render();
    }

    return 0;
}