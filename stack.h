#ifndef STACK
#define STACK

#include "list.h"
#include "fringenode.h"

List *newStack(void);

void deleteStack(List *fringe);

FringeNode *popFromStack(List *fringe);

void pushToStack(FringeNode *fn, List *fringe);

#endif /* STACK */
