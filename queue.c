#include <stdlib.h>
#include <stdio.h>

#include "fringenode.h"

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
    
            if (fn->totalCost < next->totalCost)
            {
                last->next = fn;
                fn->next = next;
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
