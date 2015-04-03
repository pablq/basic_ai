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

bool weightedGrid(int ac, char **args)
{
    bool weighted = true;

    int wFlagIndex;
    for (int i = 1; i < ac; i += 1)
    {
        if (strncmp("-w", args[i], 2))
        {
            wFlag = true;
            wFlagIndex = i;
        }
    }
    if (wFlag)
    {
        if (strncmp("n",args[wFlagIndex + 1],1) == 0) // if the arg after the -w flag is "n" then we don't want weighted
            weighted = false;
    } 
    
    return weighted;
}

// options -fn a || -fn bfs dfs ucs greedy astar -b y || -b n
bool validateArgs(int ac, char **args)
{
    bool valid = true;

    if (ac == 1)
        valid = false;
    
    bool fn = false;
    int fnIndex;
    bool b = false; 
    int bIndex;

    for (int i = 1; i < ac; i += 1) // no need to check first index
    {
        if (strncmp("-fn",args[i],3) == 0) // check if -fn flag is present
        {
            fn = true;
            fnIndex = i;
        }
        if (strncmp("-b",args[i],2) == 0) // check if -b flag is present
        {
            b = true;        
            bIndex = i;
        }
    }
    
    if (fn && b) 
    {
        if (!(bIndex - fnIndex > 0)) // -fn must come before -b for now! 
            valid =  false;
        if (!(bIndex - fnIndex >= 1)) // there must be at least one arg between -fn flag and -b flag
            valid =  false;
        if (!(ac == bIndex + 2)) // there must be exactly one argument after the -b flag (+2 because ./basic_ai is always included in args)
            valid =  false;
        
    } else if (fn) {

        if (!(ac >= fnIndex + 2)) // there must be at least one arg after -fn flag
            valid = false;

    } else if (b) {
        if (!(ac == bIndex + 2)) // there must be exactly one arg after -b flag
            valid = false;
    }

    return valid;
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
