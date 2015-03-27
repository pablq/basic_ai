#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "location.h"
#include "game.h"
#include "search.h"

int main (int argc, char *argv[])
{

    Game *game = newGame();

    char *moves = bfs(game);

    playGame(moves, game);
    
    free(moves);

    deleteGame(game);

    return 0;
}
