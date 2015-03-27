#ifndef FRINGENODE
#define FRINGENODE

#include "gamemodel.h"

typedef struct FringeNode
{
    StateNode *state;
    char *allActions;
    int costOfActions;
    struct FringeNode *next; // for linked lists ONLY
} FringeNode;

FringeNode *newFringeNode(StateNode *state, char *pastActions, int pastCost);

void deleteFringeNode(FringeNode *fn);

#endif /* FRINGE */
