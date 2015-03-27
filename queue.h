#ifndef QUEUE
#define QUEUE

#include "fringenode.h"

FringeNode *newQueue(void);

void deleteQueue(FringeNode **fringe);

FringeNode *nextInQueue(FringeNode **fringe);

void pushToQueue(FringeNode *fn, FringeNode **fringe);

#endif /* QUEUE */
