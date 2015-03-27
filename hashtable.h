#ifndef HASHTABLE
#define HASHTABLE

#include <stdbool.h>

#define TABLE_LENGTH 75

typedef struct HashTableNode
{
    char *value;
    struct HashTableNode* next;
} HashTableNode;

typedef HashTableNode *HashTable;

HashTable *newHashTable (void);

bool inHashTable(char *str, HashTable *ht);

void insertToHashTable(char *str, HashTable *ht);

void deleteHashTable(HashTable *ht);

#endif /* HASHTABLE */
