#ifndef CLOSED
#define CLOSED

#include "hashtable.h"
#include "gamemodel.h"

bool inClosed(StateNode *state, HashTable *closed)

void addToClosed(StateNode *state, HashTable *closed)

// use newHashTable() for create
// use deleteHashTable(closed) for destroy

#define CLOSED
