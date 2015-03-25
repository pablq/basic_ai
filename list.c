#include "list.h"

bool checkListSize(List *list)
{
    if (list->n_items >= list->capacity) 
    {
        int new_size = list->capacity * 2;
        
        void *new_items = realloc(list->items, sizeof(void*) * new_size);

        if (new_items == NULL) 
        {
            return false;
        }

        list->items = new_items;
        list->capacity = new_size; 
    }
    return true;
}

bool trimListSize(List *list)
{
    if (list->n_items < list->capacity) 
    {
        void *new_items = realloc(list->items, sizeof(void*) * list->n_items);
        
        if (new_items == NULL)
        {
            return false;
        }

        list->items = new_items;
        list->capacity = list->n_items;
    }
    return true;
}

//NOTE THIS FUNCTION DOESN'T DELETE ANYTHING IT JUST MOVES THE POINTER. THE MEMORY WILL STILL HAVE TO BE CLEARED.
void *popFromList(List *list)
{
    int index = list->n_items - 1;
    list->n_items = index;

    return list->items[index];
}
