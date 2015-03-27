#include <stdlib.h>
#include "gamemodel.h"

char *stateToString(StateNode *state)
{
    char * sh = malloc(sizeof(char) * 5);

    sh[0] = state->location->x + 48;
    sh[1] = state->location->y + 48;
    sh[2] = state->action;
    sh[3] = state->cost + 48;
    sh[4] = '\0';
    
    return sh; 
}
