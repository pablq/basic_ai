#ifndef PROBLEM
#define PROBLEM

#include "location.h"
#include "grid.h"
#include "list.h"

// we only mock the gamestate. we don't make use of game (though we might use some of game functions)

List *getSuccessors(Location *location, Grid *grid);

bool checkForWin(Location *location, Grid *grid);

// the char * actions will always be null terminated
// the length value does not count the null terminator
typedef struct Node
{
    Location *location;
    List *path;
} Node;

#endif /* PROBLEM */
