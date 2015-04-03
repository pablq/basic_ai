#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "search.h"

void playDFS(Game *game);
void playBFS(Game *game);
void playUCS(Game *game);
void playGreedy(Game *game);
void playAstar(Game *game);

bool validateArgs(int ac, char **arv);

int main (int argc, char *argv[])
{
    
    if (validateArgs(argc, argv))
        printf("VALID ARGS:\n");
    else
        printf("INVALID ARGS:\n");

    for (int i = 0; i < argc; i += 1)
    {
        printf("%s\n",argv[i]);
    }

    /*
    Game *game = newGame(true); // true for weighted gameboard
    playDFS(game); 
    playBFS(game);
    playUCS(game);
    playGreedy(game);
    playAstar(game);
    deleteGame(game);
    */

    return 0;
}

// options -fn a || -fn bfs dfs ucs greedy astar -b y || -b n
bool validateArgs(int ac, char **args)
{
    if (ac == 2)
        return false;
    
    bool fn = false;
    int fnIndex;
    bool b = false; 
    int bIndex;

    for (int i = 0; i < ac; i += 1)
    {
        if (strncmp("-fn",args[i],3) == 0)
        {
            fn = true;
            fnIndex = i;
        }
        if (strncmp("-b",args[i],2) == 0)
        {
            b = true;        
            bIndex = i;
        }
    }
    
    if (fn && b)
    {
        int greater = fnIndex - bIndex >= 0 ? fnIndex : bIndex;
        int lesser = fnIndex - bIndex >= 0 ? bIndex : fnIndex;
        if (!(ac >= greater + 2)) // there must be at least one arg after the last flag
            return false;
        if (fnIndex - bIndex < 1 && bIndex - fnIndex < 1) // there must be at least one arg between flags
            return false;
        
        for (int i = lesser; i < greater; i += 1)
        {
            
        }

    } else if (fn) {

        if (!(ac >= fnIndex + 2)) // there must be at least one arg after -fn flag
            return false;

    } else if (b) {
        if (!(ac == bIndex + 2)) // there must be exactly one arg after -b flag
            return false;
    }

    return true;
}

void playDFS(Game *game)
{
    printf("\nDEPTH FIRST SEARCH:\n");
    char *moves = dfs(game);
    playGame(moves, game);
    free(moves);
    game = resetGame(game);
}

void playBFS(Game *game)
{
    printf("\nBREADTH FIRST SEARCH:\n");
    char *moves = bfs(game);
    playGame(moves, game);
    free(moves);
    game = resetGame(game);
}

void playUCS(Game *game)
{
    printf("\nUNIFORM COST SEARCH:\n");
    char *moves = ucs(game);
    playGame(moves, game);
    free(moves);
    game = resetGame(game);
}

void playAstar(Game *game)
{
    printf("\nASTAR SEARCH:\n");
    char *moves = astar(game);
    playGame(moves, game);
    free(moves);
    resetGame(game);
}

void playGreedy(Game *game)
{
    printf("\nGREEDY SEARCH:\n");
    char *greedy_moves = greedy(game);
    playGame(greedy_moves, game);
    free(greedy_moves);
    game = resetGame(game);
}
