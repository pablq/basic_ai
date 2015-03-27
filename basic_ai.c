#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "location.h"
#include "game.h"
#include "search.h"

int main (int argc, char *argv[])
{

    Game *game = newGame();

    printf("DEPTH FIRST SEARCH\n");

    char *dfs_moves = dfs(game);

    playGame(dfs_moves, game);
    
    free(dfs_moves);

    game = resetGame(game);

    printf("BREADTH FIRST SEARCH\n");
    
    char *bfs_moves = bfs(game);
    
    playGame(bfs_moves, game);

    free(bfs_moves);

    deleteGame(game);

    return 0;
}
