#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "search.h"

bool validateArgs(int numArgs, char **args);
bool getAlgorithms(int numArgs, char **args, bool algorithms[5]);
bool useWeightedGrid(int ac, char **args);

void playUsingDFS(Game *game);
void playUsingBFS(Game *game);
void playUsingUCS(Game *game);
void playUsingGreedy(Game *game);
void playUsingAstar(Game *game);

int main (int argc, char *argv[])
{
    if (!validateArgs(argc, argv))
    {
        printf("USAGE: ./basic_ai [-fn <dfs> <bfs> <ucs> <greedy> <astar>] [-w]\n");
        return 1;
    }
    
    bool algorithms[5];
    if (!getAlgorithms(argc, argv, algorithms)) // getAlgorthms populates an array with bools for algorithms that
                                                // should be run on the game. it returns true if it was able to populate
    {                                           // the array and false if it was unable. the algorithms are associated with
                                                // specific indexes in the array of bools. (see function implementation)
        printf("USAGE: ./basic_ai [-fn <dfs> <bfs> <ucs> <greedy> <astar>] [-w]\n");
        return 1;
    }

    // determine whether to use weighted grid
    bool weighted = useWeightedGrid(argc, argv);
    
    // and now, game time.
    Game *game = newGame(weighted);
    
    if (algorithms[0])
        playUsingDFS(game);
    if (algorithms[1])
        playUsingBFS(game);
    if (algorithms[2])
        playUsingUCS(game);
    if (algorithms[3])
        playUsingGreedy(game);
    if (algorithms[4])
        playUsingAstar(game);

    deleteGame(game);

    return 0;
}

bool validateArgs(int numArgs, char **args)
{
    bool valid = true,
         fn = false,
         w = false; 

    int fnIndex,
        wIndex;

    for (int i = 1; i < numArgs; i += 1) // no need to check first index
    {
        if (strncmp("-fn", args[i], 3) == 0) // check if -fn flag is present
        {
            fn = true;
            fnIndex = i;
        }
        if (strncmp("-w", args[i], 2) == 0) // check if -w flag is present
        {
            w = true;        
            wIndex = i;
        }
    }

    if (numArgs > 1 && !(fn || w)) // if at least one argument is passed one of them MUST be -fn or -w
        valid = false;

    if (fn && w) 
    {
        if (!(wIndex ==  1 || fnIndex == 1)) // either -w or -fn must be the first argument after ./basic_ai
            valid = false;
        if (!(wIndex - fnIndex >= 1) && !(fnIndex - wIndex == 1)) // if wIndex is after fnIndex there must be at least one arg between them.
            valid = false;                                        // but if fnIndex is after wIndex then there must be no args between them.
        if ((wIndex > fnIndex) && !(numArgs == wIndex + 1)) // if wIndex is after fnIndex, -w must be the last arg
            valid = false;
        if ((fnIndex > wIndex) && !(numArgs > fnIndex + 1)) // if fnIndex is after wIndex, there must be at least one arg after -fn
            valid = false;
        
    } else if (fn) {

        if (fnIndex != 1) // -fn must be the first argument after ./basic_ai
            valid = false;
        if (!(numArgs >= fnIndex + 2)) // there must be at least one arg after -fn flag
            valid = false;

    } else if (w) {

        if (numArgs != 2) // -w must be the only argument after ./basic_ai
            valid = false;

    } else if (!fn && !w) {

        if (numArgs > 1)
            valid = false;
    }
    
    return valid;
}

/*

getAlgorithms accepts an array of arguments and a bool array 'algorithms' to populate.
It determines which of the algorithms should be run from the arguments passed and 
populates the algorithms array accordingly. Upon successfully populating algorithms 
getAlgorithms returns true, else it returns false.

Index Map for algorithms in bool array:
0 -> dfs
1 -> bfs
2 -> ucs
3 -> greedy
4 -> astar

*/
bool getAlgorithms(int numArgs, char **args, bool algorithms[5])
{
    bool fn = false;
    for (int i = 1; i < numArgs; i += 1)
    {
        if (strncmp("-fn", args[i], 3) == 0)
        {
            fn = true;     
        } 
    } 
    
    int total = 0;
    if (fn)
    {
        for (int i = 0; i < 5; i += 1) // set all functions to false as we'll activate them individually
        {
            algorithms[i] = false;
        }

        for (int i = 2; i < numArgs; i += 1) // no need to check second arg as it's either -fn or -w
        {
            if (strcmp("dfs", args[i]) == 0)
            {
                algorithms[0] = true;
                total += 1;

            } else if (strcmp("bfs", args[i]) == 0) {

                algorithms[1] = true;
                total += 1;

            } else if (strcmp("ucs", args[i]) == 0) {

                algorithms[2] = true;
                total += 1;

            } else if (strcmp("greedy", args[i]) == 0) {

                algorithms[3] = true;
                total += 1;

            } else if (strcmp("astar", args[i]) == 0) {

                algorithms[4] = true;
                total += 1;
            }
        }

    } else {

        total = 5;
        for (int i = 0; i < 5; i += 1) // default is all functions active
        {
            algorithms[i] = true;
        }
    }

    if (total == 0)
        return false;
    else
        return true;
}

bool useWeightedGrid(int numArgs, char **args) // searches argv for -w flag. returns true if it's present
{
    bool weighted = false;

    for (int i = 1; i < numArgs; i += 1) // no need to check first arg as it's always ./basic_ai
    {
        if (strncmp("-w", args[i], 2) == 0)
        {
            weighted = true;
        }
    }
    return weighted;
}

void playUsingDFS(Game *game)
{
    printf("\nDEPTH FIRST SEARCH:\n");
    char *moves = dfs(game);
    playGame(moves, game);
    free(moves);
    game = resetGame(game);
}

void playUsingBFS(Game *game)
{
    printf("\nBREADTH FIRST SEARCH:\n");
    char *moves = bfs(game);
    playGame(moves, game);
    free(moves);
    game = resetGame(game);
}

void playUsingUCS(Game *game)
{
    printf("\nUNIFORM COST SEARCH:\n");
    char *moves = ucs(game);
    playGame(moves, game);
    free(moves);
    game = resetGame(game);
}

void playUsingGreedy(Game *game)
{
    printf("\nGREEDY SEARCH:\n");
    char *moves = greedy(game);
    playGame(moves, game);
    free(moves);
    game = resetGame(game);
}

void playUsingAstar(Game *game)
{
    printf("\nASTAR SEARCH:\n");
    char *moves = astar(game);
    playGame(moves, game);
    free(moves);
    resetGame(game);
}
