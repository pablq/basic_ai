#include <stdio.h>
#include <ctype.h>
#include "GetString/GetString.h"
#include "game.h"
#include "grid.h"

int main (void)
{
    Game *game = newGame();

    printGrid(game->grid);

    printf("MOVES: ");
    char *moves = GetString();

    int i = 0;
    while (moves[i] != '\0')
    {
        moves[i] = tolower(moves[i]);
        i += 1;
    }

    playGame(moves, game);

    printGrid(game->grid);

    deleteGame(game);

    return 0;
}

