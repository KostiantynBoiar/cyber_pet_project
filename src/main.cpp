#include "headers/Game.h"
#include "headers/Player.h"
#include "headers/JSON_API.h"

int main()
{
    Game game;
    Player player;
    JSON_API jsonApi("gameFile.json");

    jsonApi.getActualDate();
    std::cout << jsonApi.restTimeDiff() << std::endl << jsonApi.foodTimeDiff();
    while (game.getWindowIsOpen())
    {
        game.update();
        player.update();
        game.render();
    }

    return 0;
}