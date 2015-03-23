#ifndef PROBLEM
#define PROBLEM

#include "location.h"
#include "grid.h"
#include "list.h"

Location *getStartState(Grid *grid);

bool isGoalState(Location *location, Grid *grid);

// the char * actions will always be null terminated
// the length value does not count the null terminator
typedef struct SuccessorNode
{
    Location *location;
    char action;
    int cost;
} SuccessorNode;

List *getSuccessors(Location *location, Grid *grid);

/*
typedef struct FringeNode <- for use in search algorithms
{
   SuccessorNode *node;
   List *actions;
} 
*/

#endif /* PROBLEM */
