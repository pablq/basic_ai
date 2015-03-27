#include <stdlib.h>
#include "gamemodel.h"
#include "hashtable.h"

bool inSet(StateNode *state, HashTable *closed)
{
    char *sh = stateToString(state);  
    bool inClosed = inHashTable(sh, closed);
    free(sh);
    return inClosed;
}

void addToSet(StateNode *state, HashTable *closed)
{
    char *sh = stateToString(state);
    insertToHashTable(sh, closed);  
}
