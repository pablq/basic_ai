#include <stdlib.h>
#include <string.h>

#include "fringenode.h"
#include "gamemodel.h"

FringeNode *newFringeNode(StateNode *state, char *pastActions, int pastCost)
{
    int len = strlen(pastActions);
    char* allActions = malloc((len + 2)); // pastActions + new action + '\0'
    int i = 0;
    while (i < len)
    {
        allActions[i] = pastActions[i]; 
        i += 1; 
    }
    allActions[len] = state->action;
    allActions[len + 1] = '\0';

    int costOfActions = pastCost + state->cost;

    FringeNode *fn = (FringeNode *) malloc(sizeof(FringeNode));    

    fn->state = state;
    fn->allActions = allActions;
    fn->costOfActions = costOfActions;

    /* NOTE
        fn->next is specifically for use in linked lists.
        it should always be NULL otherwise */

    fn->next = NULL;
   
    return fn;
}

void deleteFringeNode(FringeNode *fn)
{
    /* NOTE
        fn->next does not get freed here. it's specifically
        for the use of linked lists and never otherwise. in
        that case, it's the linked list's responsibility to 
        delete fringe nodes individually */

    free(fn->state->location);
    free(fn->state);
    free(fn->allActions);
    free(fn);
}
