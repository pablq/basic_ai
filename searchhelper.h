#ifndef SEARCHHELPER
#define SEARCHHELPER

#include "location.h"
#include "grid.h"
#include "list.h"
#include "game.h"

bool isGoalState(Location *location, Grid grid);

// the char * actions will always be null terminated
// the length value does not count the null terminator
typedef struct StateNode
{
    Location *location;
    char action;
    int cost;
} StateNode;

List* getSuccessorStateNodes(StateNode *parent, Grid grid);

void deleteStateNode(StateNode *node);

#endif /* SEARCHHELPER*/
