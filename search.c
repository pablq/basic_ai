#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "grid.h"
#include "list.h"
#include "util.h"
#include "hashtable.h"
#include "search.h"
#include "fringenode.h"
#include "stack.h"
#include "queue.h"
#include "gamemodel.h"

char *dfs (Game *game)
{
    printf("Depth First Search working...\n");

    // create our fringe as a FILO Stack
    List *fringe = newStack();
    
    // closed will store all the states we've already visited to avoid repeats
    HashTable *closed = newHashTable();

    // prepare state and values for first fringe node
    StateNode *startState = (StateNode *) malloc(sizeof(StateNode));
    startState->loc = malloc(sizeof(Location));
    startState->loc->x = game->start->x; // <-Here
    startState->loc->y = game->start->y; // <-Here
    startState->action = 0;
    startState->cost = 0;
   
    char *startPath = "\0";
    int startCost = 0;
    
    // build fringe node and push it to the fringe
    FringeNode *first = newFringeNode(startState, startPath, startCost);
    pushToStack(first, fringe);

    // variables for book-keeping
    long expanded = 0;
    long total_fringe = 0;
    long average_fringe = 0;
    
    // let's get goin!
    while(true)
    {
        // get the most recently added FringeNode
        FringeNode *fn = popFromStack(fringe);

        // if there was nothing there, we failed :/
        if (fn == NULL)
        {
            printf("No Solution found :(\n");

            // clean up
            deleteStack(fringe);
            deleteHashTable(closed);

            return NULL;
        } 

        // book-keeping
        expanded += 1;
        total_fringe += fringe->n_items;
        average_fringe = total_fringe / expanded;

        // how manys actions in path?
        int len = 0;
        if (fn->path != NULL)
        {
            len = strlen(fn->path);
        }

        // if this state's location is the winning state we win!
        if (sameLocation(fn->state->loc->x, fn->state->loc->y, game->goal->x, game->goal->y))
        {
            // take the path, and nullify reference to it from the FringeNode
            char *pathToVictory = fn->path;
            fn->path = NULL;

            // report stats
            printf("Total cost of solution: %d\n", fn->totalCost);
            printf("Total gamestates considered: %ld\n", expanded);
            printf("Average number of bytes in memory: %ld\n", average_fringe * sizeof(FringeNode));

            // clean up
            deleteFringeNode(fn);
            deleteStack(fringe);
            deleteHashTable(closed);

            // return the glorious path to victory!
            return pathToVictory;

        } else { // if it wasn't the winning state we must keep searching
            
            // get a list of the neighboring gamestates
            List *successors = getSuccessorStateNodes(fn->state, game->board);

            // show actual type of list's items
            StateNode **items = successors->items;

            // create a new FringeNode for each appropriate state in the list
            for (int i = 0; i < successors->n_items; i += 1)
            {
                StateNode *successor = items[i];
                
                // a state is "appropriate if it hasn't already been explored
                if (!stateInHashTable(successor, closed))
                {
                    // add to state to closed list
                    addStateToHashTable(successor, closed);

                    // create a new FringeNode with that state and old FringeNode's path/totalCost
                    FringeNode *new = newFringeNode(successor, fn->path, fn->totalCost);

                    // add it to the fringe
                    pushToStack(new, fringe);

                } else {

                    // the StateNode must be freed - it's useless now
                    free(successor->loc);
                    free(successor);
                }
            }

            // clean up our list that had contained the successors
            free(items); // successors->items
            free(successors);

            // we no longer need the old FringeNode  
            deleteFringeNode(fn);
        }
    } 
}

char *bfs(Game *game)
{
    printf("Breadth First Search working...\n");

    // create our fringe as a FIFO Queue
    FringeNode *fringe = newQueue();
    
    // closed will store all the states we've already visited to avoid repeats
    HashTable *closed = newHashTable();

    // prepare state and values for first fringe node
    StateNode *startState = (StateNode *) malloc(sizeof(StateNode));
    startState->loc = malloc(sizeof(Location));
    startState->loc->x = game->start->x; // <-Here
    startState->loc->y = game->start->y; // <-Here
    startState->action = 0;
    startState->cost = 0;
   
    char *startPath = "\0";
    int startCost = 0;
    
    // build fringe node and push it to the fringe
    FringeNode *first = newFringeNode(startState, startPath, startCost);
    pushToQueue(first, &fringe);

    // variables for book-keeping
    long expanded = 0;
    long n_items = 1; // for the first FringeNode
    long total_fringe = n_items;
    long average_fringe = 0;
    
    // let's get goin!
    while(true)
    {
        // get the most recently added FringeNode
        FringeNode *fn = nextInQueue(&fringe);

        // if there was nothing there, we failed :/
        if (fn == NULL)
        {
            printf("No Solution found :(\n");

            // clean up
            deleteQueue(&fringe);
            deleteHashTable(closed);

            return NULL;
        } 

        // book-keeping
        expanded += 1;
        n_items -= 1;
        total_fringe += n_items;
        average_fringe = total_fringe / expanded;

        // how manys actions in path?
        int len = 0;
        if (fn->path != NULL)
        {
            len = strlen(fn->path);
        }

        // if this state's location is the winning state we win!
        if (sameLocation(fn->state->loc->x, fn->state->loc->y, game->goal->x, game->goal->y))
        {
            // take the path, and nullify reference to it from the FringeNode
            char *pathToVictory = fn->path;
            fn->path = NULL;

            // report stats
            printf("Total cost of solution: %d\n", fn->totalCost);
            printf("Total gamestates considered: %ld\n", expanded);
            printf("Average number of bytes in memory: %ld\n", average_fringe * sizeof(FringeNode));

            // clean up
            deleteFringeNode(fn);
            deleteQueue(&fringe);
            deleteHashTable(closed);

            // return the glorious path to victory!
            return pathToVictory;

        } else { // if it wasn't the winning state we must keep searching
            
            // get a list of the neighboring gamestates
            List *successors = getSuccessorStateNodes(fn->state, game->board);

            // show actual type of list's items
            StateNode **items = successors->items;

            // create a new FringeNode for each appropriate state in the list
            for (int i = 0; i < successors->n_items; i += 1)
            {
                StateNode *successor = items[i];
                
                // a state is "appropriate if it hasn't already been explored
                if (!stateInHashTable(successor, closed))
                {
                    // add to state to closed list
                    addStateToHashTable(successor, closed);

                    // create a new FringeNode with that state and old FringeNode's path/totalCost
                    FringeNode *new = newFringeNode(successor, fn->path, fn->totalCost);

                    // add it to the fringe
                    pushToQueue(new, &fringe);
                   
                    // book-keeping 
                    n_items += 1;

                } else {

                    // the StateNode must be freed - it's useless now
                    free(successor->loc);
                    free(successor);
                }
            }

            // clean up our list that had contained the successors
            free(items); // successors->items
            free(successors);

            // we no longer need the old FringeNode  
            deleteFringeNode(fn);
        }
    } 
}
