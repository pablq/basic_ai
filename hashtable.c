#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "util.h"
#include "gamemodel.h"

#define TABLE_LENGTH 75

unsigned int getHashTableIndex(char *value);

HashTable *newHashTable (void)
{
    HashTable *ht = malloc(sizeof(HashTableNode*) * TABLE_LENGTH);
    for (int i = 0; i < TABLE_LENGTH; i += 1)
    {
        ht[i] = NULL;
    }
    return ht; 
}

HashTableNode *newHashTableNode()
{
    HashTableNode *htn = malloc(sizeof(HashTableNode)); 
    htn->value = NULL;
    htn->next = NULL;
    return htn;
}

bool inHashTable(char *value, HashTable *ht)
{
    int index = getHashTableIndex(value);

    HashTableNode *last = ht[index];

    if (last == NULL)
    {
        return false;
    }
    
    do {

        HashTableNode *next = last->next;

        if (strcmp(value, last->value) == 0)
        {
            return true;
        }

        last = next;

    } while (last != NULL); 
    
    return false;    
}

void insertToHashTable(char *value, HashTable *ht)
{
    int index = getHashTableIndex(value);
    
    HashTableNode *htn = newHashTableNode();
    htn->value = value;
    
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
                free(last->value);
                free(last);
                last = next;
                next = next->next;
            }
            free(last->value);
            free(last); 
        }
    }
    free(ht);
}

// DJB2 - www.cse.yorku.ca/~oz/hash.html
unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c,
        i = 0;

    while (str[i] != '\0')
    {
        c = str[i]; 
        hash = ((hash << 5) + hash) + c; /* hash * 33 + x */
        i += 1;
    }
    return hash;
}

unsigned int getHashTableIndex(char *str) 
{
    return hash(str) % TABLE_LENGTH;
}

// SPECIFIC FUNCTIONS FOR GAMESTATES

bool stateInHashTable(StateNode *state, HashTable *closed)
{
    char *sh = stateToString(state);  
    bool inClosed = inHashTable(sh, closed);
    free(sh);
    return inClosed;
}

void addStateToHashTable(StateNode *state, HashTable *closed)
{
    char *sh = stateToString(state);
    insertToHashTable(sh, closed);  
}
