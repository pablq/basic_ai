#ifndef QUEUE
#define QUEUE

#include "fringenode.h"

typedef struct Heuristic
{
    void *data;
    int (*heurfn)(FringeNode *fn, void *data);    
} Heuristic;

FringeNode *newQueue(void);

void deleteQueue(FringeNode **fringe);

FringeNode *nextInQueue(FringeNode **fringe);

void pushToQueue(FringeNode *fn, FringeNode **fringe);

void pushToQueueByCost(FringeNode *fn, FringeNode **fringe);

void pushToQueueByHeuristic(FringeNode *fn, Heuristic *h, FringeNode **fringe);

#endif /* QUEUE */
