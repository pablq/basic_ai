#include <stdio.h>
#include "game.h"
#include "search.h"

int main (int argc, char *argv[])
{
    Game *game = newGame();

    char *moves = dfs(game);

    playGame(moves, game);

    deleteGame(game);

    printf("argc: %d\n",argc);

    return 0;
}
