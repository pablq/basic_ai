#ifndef GAME
#define GAME
#include "game.h"
#endif

#ifndef GRID
#define GRID
#include "grid.h"
#endif

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

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
