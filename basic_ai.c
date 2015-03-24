#include <stdio.h>
#include "game.h"
#include "grid.h"

int main (void)
{
    Game *game = newGame();

    char moves[] = {'n','e','e','e','s','w','s','\0'};

    playGame(moves, game);

    deleteGame(game);

    return 0;
}
