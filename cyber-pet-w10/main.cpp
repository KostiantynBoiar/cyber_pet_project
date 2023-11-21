#include "Game.h"
#include "Player.h"
#include "JSON_API.h"

int main()
{
    JSON_API jsonApi("gameFile.json");
    Game game;
    Player player;

    
    while (game.getWindowIsOpen())
    {
        game.update();
        player.update();
        game.render();
    }

    return 0;
}