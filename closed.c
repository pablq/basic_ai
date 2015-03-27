#include "gamemodel.h"
#include "hashtable.h"

bool inClosed(StateNode *state, HashTable *closed)
{
    char *sh = stateToString(state);  
    bool inClosed = inHashTable(sh, closed);
    free(sh);
    return inClosed;
}

void addToClosed(StateNode *state, HashTable *closed)
{
    char *sh = stateToString(state);
    insertToHashTable(sh, closed);  
}
