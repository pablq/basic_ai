#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "grid.h"
#include "list.h"
#include "util.h"
#include "searchhelper.h"
#include "search.h"

bool checkClosedSize(List *list);
bool checkFringeSize(List *list);
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
    if (checkFringeSize(fringe))
    {
        FringeNode **items = (FringeNode **)fringe->items;
        items[fringe->n_items] = fn;
        fringe->items = items;
        fringe->n_items += 1; 
    }
}

List *newClosed(void)
{
    List *closed = (List *) malloc(sizeof(List));
    Location **items = (Location **) malloc(sizeof(Location *) * 32);
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
    if (checkClosedSize(closed))
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
    int len = strlen(pastActions);
    char *allActions = malloc(sizeof(char) * (len + 2));
    allActions = strcpy(allActions, pastActions);
    /*while (i < len)
    {
        allActions[i] = pastActions[i]; 
        i += 1; 
    }*/ 
    allActions[len] = state->action;
    allActions[len + 1] = '\0';

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

    StateNode *state = getFirstStateNode(game->start->x,game->start->y);
   
    FringeNode *first = newFringeNode(state,"", 0);

    addToFringe(first, fringe);

    while(true)
    {
        FringeNode *thisNode = popFromFringe(fringe);

        if (thisNode == NULL) {
            /*
            deleteFringeNode(thisNode);
            deleteFringe(fringe);
            deleteClosed(closed);
            */
            return NULL;
        } 

        if (sameLocation(thisNode->state->location->x, thisNode->state->location->y, game->goal->x, game->goal->y)) {
            /*
            deleteFringeNode(thisNode);
            deleteFringe(fringe);
            deleteClosed(closed);
            */
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

            free(successors);
        }

        deleteFringeNode(thisNode);
    } 
}
bool checkClosedSize(List *list)
{
    if (list->n_items >= list->capacity) 
    {
        printf("re-allocing closed\n");
        int new_size = list->capacity * 2;
        
        Location **items = (Location**) list->items;
        items = realloc(items, sizeof(Location*) * new_size);

        if (items == NULL) 
        {
            return false;
        }

        list->items = items;
        list->capacity = new_size; 
    }
    return true;
}
bool checkFringeSize(List *list)
{
    if (list->n_items >= list->capacity) 
    {
        printf("re-allocing fringe\n");
        int new_size = list->capacity * 2;
        
        FringeNode **items = (FringeNode**) list->items;
        
        items = realloc(items, sizeof(FringeNode*) * new_size);

        if (items == NULL) 
        {
            return false;
        }

        list->items = items;
        list->capacity = new_size; 
    }
    return true;
}
