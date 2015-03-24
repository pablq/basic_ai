#include <stdio.h>
#include "game.h"
#include "grid.h"

int main (void)
{
    Game *game = newGame();

    printGrid(game->grid);

    char moves[] = {'n','e','e','e','s','w','s','\0'};

    playGame(moves, game);

    printGrid(game->grid);

    deleteGame(game);

    return 0;
}
