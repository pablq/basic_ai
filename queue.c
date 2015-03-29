#include <stdlib.h>
#include <stdio.h>

#include "fringenode.h"
#include "util.h"
#include "queue.h"

FringeNode *newQueue(void)
{
    return NULL;
}

void pushToQueue(FringeNode *fn, FringeNode **fringe)
{
    FringeNode *last = *fringe;
    if (last == NULL)
    {
        *fringe = fn;
        
    } else {

        FringeNode *next = last->next;
        while (next != NULL)
        {
            last = next;
            next = next->next;
        }
        last->next = fn;
    }
}

void pushToQueueByCost(FringeNode *fn, FringeNode **fringe)
{
    FringeNode *last = *fringe;
    if (last == NULL)
    {
        *fringe = fn;

    } else {
       
        FringeNode *next = last->next;
        while (next != NULL)
        {
            if (fn->totalCost < next->totalCost) // the use of < instead of <= is relevant.
            {                                    // this gives preference to the older node.
                last->next = fn;                 // the result is behavior that searches shallower
                fn->next = next;                 // nodes before deeper ones (if their cost is the same).
                break; 

            } else {

                last = next;
                next = next->next;
            }
        }
        last->next = fn;
    }
}

void pushToQueueByHeuristic(FringeNode *fn, Heuristic *h, FringeNode **fringe)
{
    FringeNode *last = *fringe;
    if (last == NULL)
    {
        *fringe = fn;

    } else {
       
        FringeNode *next = last->next;
        while (next != NULL)
        {
            if (h->heurfn(fn, h->data) <= h->heurfn(next, h->data)) // the use of <= instead of < is relevant.
            {                                                       // this gives preference to the newer node.
                last->next = fn;                                    // the result is behavior that searches deeper
                fn->next = next;                                    // nodes before shallow ones (if their heuristic is the same)
                break; 

            } else {

                last = next;
                next = next->next;
            }
        }
        last->next = fn;
    }
}

void deleteQueue(FringeNode **fringe)
{
    FringeNode *last = *fringe;
    if (last != NULL)
    {
        FringeNode *next = last->next;
        while (next != NULL)
        {
            deleteFringeNode(last);
            last = next;
            next = next->next;
        }
        deleteFringeNode(last);
    }
}

FringeNode *nextInQueue(FringeNode **fringe)
{
    FringeNode *first = *fringe;
    if (first == NULL)
    {
        return NULL;

    } else {

        FringeNode *next = first->next;
        *fringe = next;
    }
    return first;
}
