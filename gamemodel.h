#ifndef GAMEMODEL
#define GAMEMODEL

#include "location.h"
#include "grid.h"
#include "list.h"

int costFn(Location *location, Grid board);

typedef struct StateNode
{
    Location *location;
    char action;
    int cost;
} StateNode;

char *stateToString(StateNode *state);

List* getSuccessorStateNodes(StateNode *parent, Grid grid);

#endif /* GAMEMODEL */
