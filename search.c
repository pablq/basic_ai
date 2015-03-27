#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "grid.h"
#include "list.h"
#include "util.h"
#include "hashtable.h"
#include "search.h"
#include "fringe.h"
#include "gamemodel.h"
#include "set.h"

char *dfs (Game *game)
{
    printf("Depth First Search working...\n");

    List *fringe = newFringe();
    
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

    addToFringe(first, fringe);

    long expanded = 0;
    long total_fringe = 0;
    long average_fringe = 0;
    
    while(true)
    {
        FringeNode *thisNode = popFromFringe(fringe);

        if (thisNode == NULL)
        {
            printf("No Solution found :(\n");

            deleteFringe(fringe);
            deleteHashTable(closed);

            return NULL;
        } 

        expanded += 1;
        total_fringe += fringe->n_items;
        average_fringe = total_fringe / expanded;

        StateNode *thisState = thisNode->state;
        Location *thisLocation = thisState->location;
        char *pastActions = thisNode->allActions;
        int lenPastActions = 0;
        if (pastActions != NULL)
        {
            lenPastActions = strlen(pastActions);
        }
        int pastCostOfActions = thisNode->costOfActions;

        if (sameLocation(thisLocation->x, thisLocation->y, game->goal->x, game->goal->y))
        {
            char *pathToVictory = malloc(lenPastActions + 1);

            for (int i = 0; i <= lenPastActions; i += 1)
            {
                pathToVictory[i] = pastActions[i];
            }

            printf("Total movement cost of solution: %d\n", pastCostOfActions);
            printf("Total locations explored: %ld\n", expanded);
            printf("Average number of locations stored: %ld\n", average_fringe);

            free(thisLocation);
            free(thisState);
            free(pastActions);
            free(thisNode);

            deleteFringe(fringe);
            deleteHashTable(closed);

            return pathToVictory;

        } else {
            
            Grid board = game->board;
            List *successors = getSuccessorStateNodes(thisState, board);

            StateNode **items = successors->items;
            int len = successors->n_items;
            for (int i = 0; i < len; i += 1)
            {
                StateNode *successor = items[i];
                
                if (!inSet(successor, closed))
                {
                    addToSet(successor, closed);

                    FringeNode *fn = newFringeNode(successor, pastActions, pastCostOfActions);

                    addToFringe(fn, fringe);

                } else {

                    Location *successor_loc = successor->location;
                    free(successor_loc);
                    free(successor);
                }
            }
            
            free(items); 
            free(successors);

            free(thisLocation);
            free(thisState);
            free(pastActions);
            free(thisNode);
        }
    } 
}

int costFn(Location *location, Grid board)
{
    int val = board[location->x][location->y];
    return val;
}

