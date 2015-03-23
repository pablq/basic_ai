#include <stdio.h>
#include "GetString/GetString.h"
#include "game.h"
#include "grid.h"

int main (void)
{
    Game *game = newGame();

    printGrid(game->grid);

    printf("MOVES: ");
    char *moves = GetString();

    playGame(moves, game);

    printGrid(game->grid);

    deleteGame(game);

    return 0;
}

