#ifndef SET
#define SET

#include "hashtable.h"
#include "gamemodel.h"

bool inSet(StateNode *state, HashTable *closed);

void addToSet(StateNode *state, HashTable *closed);

// use newHashTable() for create
// use deleteHashTable(closed) for destroy

#endif /* SET */
