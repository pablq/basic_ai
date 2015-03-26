#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#include "util.h"

#define TABLE_LENGTH 75

unsigned int getHashTableIndex(char *str);

unsigned long hash(char *str);

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
    //printf("newHashTableNode\n");
    HashTableNode *htn = malloc(sizeof(HashTableNode)); 
    htn->value = NULL;
    htn->next = NULL;
    
    return htn;
}

bool inHashTable(char *str, HashTable *ht)
{
    printf("inHashTable : ");

    int index = getHashTableIndex(str);

    HashTableNode *last = ht[index];

    if (last == NULL)
    {
        printf("false\n");
        return false;
    }
    
    do {

        HashTableNode *next = last->next;

        if (strcmp(str,last->value) == 0)
        {
            printf("true\n");
            return true;
        }

        last = next;

    } while (last != NULL); 
    
    printf("false\n");
    return false;    
}

void insertToHashTable(char *val, HashTable *ht)
{
    printf("insertToHashTable : %s\n",val);

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

unsigned int getHashTableIndex(char *str) 
{
    return hash(str) % TABLE_LENGTH;
}

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;
    
    int i = 0;
    while (str[i] != '\0')
    {
        c = str[i]; 
        hash = ((hash << 5) + hash) + c; /* hash * 33 + x */
        i += 1;
    }

    return hash;
}
