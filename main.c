#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "search.h"

int main (int argc, char *argv[])
{
    Game *game = newGame(true); // true for weighted gameboard

    printf("\nDEPTH FIRST SEARCH:\n");
    char *dfs_moves = dfs(game);
    playGame(dfs_moves, game);
    free(dfs_moves);
    game = resetGame(game);

    printf("\nBREADTH FIRST SEARCH:\n");
    char *bfs_moves = bfs(game);
    playGame(bfs_moves, game);
    free(bfs_moves);
    game = resetGame(game);
    
    printf("\nUNIFORM COST SEARCH:\n");
    char *ucs_moves = ucs(game);
    playGame(ucs_moves, game);
    free(ucs_moves);
    game = resetGame(game);
    
    printf("\nGREEDY SEARCH:\n");
    char *greedy_moves = greedy(game);
    playGame(greedy_moves, game);
    free(greedy_moves);
    game = resetGame(game);

    printf("\nASTAR SEARCH:\n");
    char *astar_moves = astar(game);
    playGame(astar_moves, game);
    free(astar_moves);
    deleteGame(game);

    return 0;
}
