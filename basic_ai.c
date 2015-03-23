#include <stdio.h>
#include "game.h"
#include "grid.h"

int main (void)
{
    Game *game = newGame();

    printGrid(game->grid);

    char moves[] = {'N','E','E','E','S','W','S','\0'};

    // printf("N E E E S W S \\O\n");

    play(moves, game);

    printGrid(game->grid);

    deleteGame(game);

    return 0;
}
