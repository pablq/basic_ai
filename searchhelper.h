#ifndef SEARCHHELPER
#define SEARCHHELPER

#include "location.h"
#include "grid.h"
#include "list.h"
#include "game.h"

bool isGoalState(Location *location, Grid *grid);

// the char * actions will always be null terminated
/ the length value does not count the null terminator
typedef struct StateNode
{
    Location *location;
    char action;
    int cost;
} StateNode;

StateNode *getFirstStateNode(StateNode *first_node, Game *game);

List *getSuccessors(List *successors, StateNode *parent, Grid *grid); // this function assumes successors has 4 available slots.

void deleteStateNode(StateNode *node);

typedef struct FringeNode
{
    StateNode *state;
    char *allActions;
    int costOfActions;
}

#endif /* SEARCHHELPER*/
