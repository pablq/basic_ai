#include <stdlib.h>

#include "fringenode.h"
#include "list.h"

List *newStack(void)
{
    List* fringe = (List *) malloc(sizeof(List));

    FringeNode **items = (FringeNode **) malloc(sizeof(FringeNode*) * 32);
    fringe->items = items;
    fringe->capacity = 32;
    fringe->n_items = 0;

    return fringe;
}

void deleteStack(List *fringe)
{
    FringeNode **items = (FringeNode **)fringe->items;
    for (int i = 0; i < fringe->n_items; i += 1)
    {
        FringeNode *fn = (FringeNode *)items[i];
        deleteFringeNode(fn);
    }
    free(items);
    free(fringe);
}

FringeNode *popFromStack(List *fringe)
{
    if (fringe->n_items < 1)
    {
        return NULL;

    } else {

        // get list of pointers
        FringeNode **items = (FringeNode **)fringe->items;
        
        // decriment count of items
        fringe->n_items -= 1;

        // grab pointer to last item
        FringeNode *fn = (FringeNode *)items[fringe->n_items];

        // eliminate pointer from list
        items[fringe->n_items] = NULL;
        
        // return pointer    
        return fn;
    }
}

// helper function for pushToStack
bool checkStackSize(List *list)
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

void pushToStack(FringeNode *fn, List *fringe)
{
    if (checkStackSize(fringe))
    {
        FringeNode **items = (FringeNode **) fringe->items;
        items[fringe->n_items] = fn;
        fringe->items = items;
        fringe->n_items += 1; 
    }
}
