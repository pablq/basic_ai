#ifndef FRINGE
#define FRINGE

#include "model.h"

typedef struct FringeNode
{
    StateNode *state;
    char *allActions;
    int costOfActions;
} FringeNode;

#endif /* FRINGE */
