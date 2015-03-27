#ifndef FRINGE
#define FRINGE

#include "gamemodel.h"

typedef struct FringeNode
{
    StateNode *state;
    char *allActions;
    int costOfActions;
} FringeNode;

void deleteFringe(List *fringe);

FringeNode *popFromFringe(List *fringe);

void addToFringe(FringeNode *fn, List *fringe);

bool checkFringeSize(List *list);

FringeNode *newFringeNode(StateNode *state, char *pastActions, int pastCost)

#endif /* FRINGE */
