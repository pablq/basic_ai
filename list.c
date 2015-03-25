#include "list.h"

bool checkSize(List *list)
{
    if (list->n_items >= list->capacity) {
        int new_size = list->capacity * 2;
        list->items = realloc(list->items, sizeof() * new_size);
        list->capacity = new_size; 
    }
}
