#include <stdlib.h>
#include "hashtable.h"
#include "util.h"

#define TABLE_LENGTH 75

int getHashTableIndex(void *pointer);

HashTable *newHashTable (void)
{
    HashTable *ht = malloc(sizeof(HashTableNode*) * TABLE_LENGTH);
    for (int i = 0; i < TABLE_LENGTH; i += 1)
    {
        ht[i] = NULL;
    }
    return ht; 
}

HashTableNode *newHashTableNode ()
{
    HashTableNode *htn = malloc(sizeof(HashTableNode)); 
    htn->value = NULL;
    htn->next = NULL;
    
    return htn;
}

bool isInTable(void *val, HashTable *ht)
{
    int index = getHashTableIndex(val);

    HashTableNode *last = ht[index];

    if (last == NULL)
    {
        return false;
    }
    
    do {

        HashTableNode *next = last->next;

        if (val == last->value)
        {
            return true;
        }

        last = next;

    } while (last != NULL); 
    
    return false;    
}

void insertToHashTable(void *val, HashTable *ht)
{
    int index = getHashTableIndex(val);
    
    HashTableNode *htn = newHashTableNode();
    htn->value = val;
    
    HashTableNode *last = ht[index];
    if (last == NULL)
    {
        ht[index] = htn;
    } else {
        HashTableNode *next = last->next;
        while (next != NULL)
        {
            last = next;
            next = next->next;
        }
        last->next = htn;
    }
}

void deleteHashTable(HashTable *ht)
{
    for (int i = 0; i < TABLE_LENGTH; i += 1)
    {
        HashTableNode *last = ht[i];
        if (last != NULL)
        {
            HashTableNode *next = last->next;
            while (next != NULL)
            {    
                free(last);
                last = next;
                next = next->next;
            }
            free(last); 
        }
    }
    free(ht);
}

int getHashTableIndex(void *pointer) 
{
    return pointerHash(pointer) % TABLE_LENGTH;
}
