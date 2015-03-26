#ifndef HASHTABLE
#define HASHTABLE

typedef struct HashTableNode
{
    void *value;
    struct HashTableNode* next;
} HashTableNode;

typedef HashTableNode *HashTable;

HashTable *newHashTable (void);

bool isInTable(void *val, HashTable *ht);

void insertToHashTable(void *val, HashTable *ht);

void deleteHashTable(HashTable *ht);

#endif /* HASHTABLE */
