#ifndef PROBLEM
#define PROBLEM

#include "location.h"
#include "grid.h"
#include "list.h"

bool isGoalState(Location *location, Grid *grid);

// the char * actions will always be null terminated
// the length value does not count the null terminator
typedef struct Node 
{
    Location *location;
    char action;
    int cost;
} Node;

Node *getFirstNode(Node *first_node, Grid *grid);

List *getSuccessors(List *successors, Node *parent, Grid *grid); // this function assumes successors has 4 available slots.

void deleteNode(Node *node);

#endif /* PROBLEM */
