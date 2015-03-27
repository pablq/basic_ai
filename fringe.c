#include <stdlib.h>

#include "fringe.h"
#include "gamemodel.h"
#include "list.h"

FringeNode *newFringeNode(StateNode *state, char *pastActions, int pastCost)
{
    int len = strlen(pastActions);
    char* allActions = malloc((len + 2)); // pastActions + new action + '\0'
    int i = 0;
    while (i < len)
    {
        allActions[i] = pastActions[i]; 
        i += 1; 
    }
    allActions[len] = state->action;
    allActions[len + 1] = '\0';

    int costOfActions = pastCost + state->cost;

    FringeNode *fn = (FringeNode *) malloc(sizeof(FringeNode));    

    fn->state = state;
    fn->allActions = allActions;
    fn->costOfActions = costOfActions;
   
    return fn;
}

bool checkFringeSize(List *list)
{
    if (list->n_items >= list->capacity) 
    {
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
        free(fn->state->location);
        free(fn->state);
        free(fn->allActions);
        free(fn);
    }
    free(items);
    free(fringe);
}

FringeNode *popFromFringe(List *fringe)
{
    if (fringe->n_items < 1)
    {
        return NULL;

    } else {

        // get list of pointers
        FringeNode **items = (FringeNode **)fringe->items;
        
        // grab pointer to last item
        FringeNode *fn = (FringeNode *)items[fringe->n_items - 1];

        // decriment count of items
        fringe->n_items -= 1;

        // eliminate pointer from list
        items[fringe->n_items] = NULL;
        
        // return pointer    
        return fn;
    }
}

void addToFringe(FringeNode *fn, List *fringe)
{
    if (checkFringeSize(fringe))
    {
        FringeNode **items = (FringeNode **) fringe->items;
        items[fringe->n_items] = fn;
        fringe->items = items;
        fringe->n_items += 1; 
    }
}
