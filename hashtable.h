#ifndef HASHTABLE
#define HASHTABLE

#include <stdbool.h>
#include "gamemodel.h"

typedef struct HashTableNode
{
    char *value;
    struct HashTableNode* next;
} HashTableNode;

typedef HashTableNode *HashTable;

HashTable *newHashTable (void);

void deleteHashTable(HashTable *ht);

bool stateInHashTable(StateNode *state, HashTable *closed);

void addStateToHashTable(StateNode *state, HashTable *closed);

#endif /* HASHTABLE */
