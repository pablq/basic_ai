#ifndef LIST
#define LIST

#include <stdbool.h>

typedef struct List
{
    void *items;
    int nItems;
    int capacity;

} List;

#endif /* LIST */
