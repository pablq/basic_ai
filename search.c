#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "grid.h"
#include "list.h"
#include "util.h"
#include "searchhelper.h"
#include "search.h"

List *newFringe(void)
{
    List* fringe = (List *) malloc(sizeof(List));

    FringeNode **items = (FringeNode **) malloc(sizeof(FringeNode*) * 32);
    fringe->items = items;
    fringe->capacity = 32;
    fringe->n_items = 0;

    return fringe;
}

void deleteFringe(List *fringe)
{
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
    if (fringe->n_items < 1)
    {
        return NULL;

    } else {

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

List *newClosed(void)
{
    List *closed = (List *) malloc(sizeof(List));
    Location **items = (Location **) malloc(sizeof(Location) * 32);
    closed->items = items;
    closed->capacity = 32;
    closed->n_items = 0;
    
    return closed;
}

void deleteClosed(List *closed)
{
    Location **items = (Location **)closed->items;
    for (int i = 0, len = closed->n_items; i < len; i += 1)
    {
        Location *location = (Location *) items[i];
        free(location);
    }
    free(closed->items);
    free(closed);
}

bool inClosed(Location *location, List *closed)
{
    Location **items = (Location **) closed->items;
    for (int i = 0, len = closed->n_items; i < len; i += 1)
    {
        Location *temp = items[i];
        if(sameLocation(location->x,location->y,temp->x,temp->y))
        {
            return true;
        }
    } 
    return false;
}

void addToClosed(Location *location, List *closed)
{
    if (checkListSize(closed))
    {
        Location **items = closed->items;
        items[closed->n_items] = location;
        closed->items = items;
        closed->n_items += 1;
    }
}

// accepts the new state, and the old fringenode's allActions and costOfActions
FringeNode *newFringeNode(StateNode *state, char *pastActions, int pastCost)
{
    int len = strlen(pastActions), i = 0;
    char *allActions = malloc(sizeof(char) * (len + 2));
    while (i < len)
    {
        //printf("%c",pastActions[i]);
        allActions[i] = pastActions[i]; 
        i += 1; 
    } 
    allActions[i] = state->action;
    allActions[i+1] = '\0';
    //printf("%c\n",allActions[i]);

    int costOfActions = pastCost + state->cost;

    FringeNode *fn = (FringeNode *) malloc(sizeof(FringeNode));    
    fn->state = state;
    fn->allActions = allActions;
    fn->costOfActions = costOfActions;
   
    return fn;
}

void deleteFringeNode(FringeNode *fn)
{
    deleteStateNode(fn->state);
    free(fn->allActions);
    free(fn);
}

char *dfs (Game *game)
{
    List *fringe = newFringe();
    
    List *closed = newClosed();

    StateNode *state = getFirstStateNode(game);
   
    FringeNode *first = newFringeNode(state,"\0", 0);

    addToFringe(first, fringe);

    while(true)
    {
        FringeNode *thisNode = popFromFringe(fringe);

        //printf("thisNode->state->location->x : %d, thisNode->state->location->y : %d\n",thisNode->state->location->x,thisNode->state->location->y);

        if (thisNode == NULL) {
            return NULL;
        } 

        if (sameLocation(thisNode->state->location->x, thisNode->state->location->y, game->goal->x, game->goal->y)) {
            return thisNode->allActions;
        } else {
            
            char *pastActions = thisNode->allActions;
            int pastCost = thisNode->costOfActions;

            List *successors = getSuccessors(thisNode->state, game->board);

            int len = successors->n_items;
            for (int i = 0; i < len; i += 1)
            {
                StateNode **items = successors->items;
                StateNode *successor = items[i];
                
                if (!inClosed(successor->location, closed))
                {
                    addToClosed(successor->location, closed);
                    FringeNode *fn = newFringeNode(successor, pastActions, pastCost);
                    addToFringe(fn, fringe);
                }
            }
        }

        //deleteFringeNode(thisNode);
    } 
}
