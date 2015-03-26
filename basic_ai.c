#include <stdio.h>
#include <string.h>
#include "game.h"
#include "search.h"

int main (int argc, char *argv[])
{
    Game *game = newGame();

    char *moves = dfs(game);

    printf("%s\n",moves);

    playGame(moves, game);

    deleteGame(game);

    return 0;
}
