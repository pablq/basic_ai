#ifndef LIST
#define LIST

#include <stdbool.h>

typedef struct List
{
    void *items;
    int n_items;
    int capacity;
} List;

#endif /* LIST */
