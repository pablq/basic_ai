#ifndef GAMEMODEL
#define GAMEMODEL

#include "location.h"
#include "grid.h"
#include "list.h"

typedef struct StateNode
{
    Location *loc;
    char action;
    int cost;
} StateNode;

char *stateToString(StateNode *state);

List* getSuccessorStateNodes(StateNode *parent, Grid grid);

#endif /* GAMEMODEL */
