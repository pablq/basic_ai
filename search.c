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
#include "gamemodel.h"

char *dfs (Game *game)
{
    printf("Depth First Search working...\n");

    List *fringe = newStack();
    
    HashTable *closed = newHashTable();

    StateNode *startState = (StateNode *) malloc(sizeof(StateNode));
    Location *l = malloc(sizeof(Location));
    l->x = game->start->x;
    l->y = game->start->y;
    startState->location = l;
    startState->action = 0;
    startState->cost = 0;
   
    char *startPath = "\0";
    int startCost = 0;

    FringeNode *first = newFringeNode(startState, startPath, startCost);

    pushToStack(first, fringe);

    long expanded = 0;
    long total_fringe = 0;
    long average_fringe = 0;
    
    while(true)
    {
        FringeNode *fn = popFromStack(fringe);

        if (fn == NULL)
        {
            printf("No Solution found :(\n");

            deleteStack(fringe);
            deleteHashTable(closed);

            return NULL;
        } 

        expanded += 1;
        total_fringe += fringe->n_items;
        average_fringe = total_fringe / expanded;

        StateNode *s = fn->state;
        char *path = fn->allActions;
        int len = 0;
        if (path != NULL)
        {
            len = strlen(path);
        }
        int cost = fn->costOfActions;

        if (sameLocation(s->location->x, s->location->y, game->goal->x, game->goal->y))
        {
            char *pathToVictory = malloc(len + 1);

            // copies all chars include null terminator
            for (int i = 0; i <= len; i += 1)
            {
                pathToVictory[i] = path[i];
            }

            printf("Total movement cost of solution: %d\n", cost);
            printf("Total locations explored: %ld\n", expanded);
            printf("Average number of locations stored: %ld\n", average_fringe);

            /*
            free(s->location);
            free(s);
            free(path);
            free(fn);
            */

            deleteFringeNode(fn);

            deleteStack(fringe);
            deleteHashTable(closed);

            return pathToVictory;

        } else {
            
            Grid board = game->board;
            List *successors = getSuccessorStateNodes(s, board);

            StateNode **items = successors->items;
            int len = successors->n_items;
            for (int i = 0; i < len; i += 1)
            {
                StateNode *successor = items[i];
                
                if (!stateInHashTable(successor, closed))
                {
                    addStateToHashTable(successor, closed);

                    FringeNode *new = newFringeNode(successor, path, cost);

                    pushToStack(new, fringe);

                } else {

                    free(successor->location);
                    free(successor);
                }
            }
            
            free(items); 
            free(successors);

            deleteFringeNode(fn);
            /*
            free(thisLocation);
            free(thisState);
            free(pastActions);
            free(thisNode);
            */
        }
    } 
}
