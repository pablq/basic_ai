#include <stdio.h>
#include "game.h"
#include "grid.h"

int main (int argc, char *argv[])
{
    Game *game = newGame();

    char moves[] = {'n','e','e','e','s','w','s','\0'};

    playGame(moves, game);

    deleteGame(game);

    printf("argc: %d\n",argc);

    return 0;
}
