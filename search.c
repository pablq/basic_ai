#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "grid.h"
#include "list.h"
#include "searchhelper.h"
#include "search.h"

List *newFringe(void)
{
    // printf("newFringe\n");
    List* fringe = (List *) malloc(sizeof(List));

    FringeNode **items = (FringeNode **) malloc(sizeof(FringeNode*) * 32);
    fringe->items = items;
    fringe->capacity = 32;
    fringe->n_items = 0;

    return fringe;
}

void deleteFringe(List *fringe)
{
    
    // printf("deleteFringe\n");
    FringeNode **items = (FringeNode **)fringe->items;
    for (int i = 0; i < fringe->n_items; i += 1)
    {
        FringeNode *fn = (FringeNode *)items[i];
        free(fn);
    }
    free(fringe->items);
    free(fringe);
}

FringeNode *popFromFringe(List *fringe)
{
    //printf("popFromFringe\n");
    if (fringe->n_items < 1)
    {
        //printf("ISNULL\n");
        return NULL;
    } else {
        //printf("DOWORK\n");
        FringeNode **items = (FringeNode **)fringe->items;
        FringeNode *fn = items[fringe->n_items - 1];
        fringe->n_items -= 1;
        return fn;
    }
}

void addToFringe(FringeNode *fn, List *fringe)
{
    //printf("addToFringe\n");
    if (checkListSize(fringe))
    {
        FringeNode **items = fringe->items;
        items[fringe->n_items] = fn;
        fringe->items = items;
        fringe->n_items += 1; 
    }
}


// accepts the new state, and the old fringenode's allActions and costOfActions
FringeNode *newFringeNode(StateNode *state, char *pastActions, int pastCost)
{
    //printf("newFringeNode\n");
    int len = strlen(pastActions), i = 0;
    char *allActions = malloc(sizeof(char) * (len + 1));
    while (i < len)
    {
        allActions[i] = pastActions[i]; 
        i += 1; 
    } 
    allActions[i] = state->action;

    int costOfActions = pastCost + state->cost;

    FringeNode *fn = (FringeNode *) malloc(sizeof(FringeNode));    
    fn->state = state;
    fn->allActions = allActions;
    fn->costOfActions = costOfActions;
   
    return fn;
}

char *dfs (Game *game)
{
    //printf("dfs\n");
    List *fringe = newFringe();
    /*
    Set *closed = newHashTable();
    */

    StateNode *state = getFirstStateNode(game);
   
    FringeNode *first = newFringeNode(state,"\0", 0);

    addToFringe(first, fringe);

    while(true)
    {
        printf("%d\n",fringe->n_items);

        FringeNode *thisNode = popFromFringe(fringe);

        if (thisNode == NULL) {
            return NULL;
        } 
        if (sameLocation(thisNode->state->location->x, thisNode->state->location->y, game->goal->x, game->goal->y)) {
            return thisNode->allActions;
        }

        else {
            
            char *pastActions = thisNode->allActions;
            int pastCost = thisNode->costOfActions;

            List *successors = getSuccessors(thisNode->state, game->board);

            int len = successors->n_items;
            for (int i = 0; i < len; i += 1)
            {
                StateNode **items = successors->items;
                StateNode *successor = items[i];
                /*
                if (!locationInClosed(successor->location, closed))
                {
                    addToClosed(successor->location);
                */
                    FringeNode *fn = newFringeNode(successor, pastActions, pastCost);
                    addToFringe(fn, fringe);
                /*
                }
                */ 
            }
        }
    } 
}
