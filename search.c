#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"
#include "grid.h"
#include "list.h"
#include "util.h"
#include "hashtable.h"
#include "searchhelper.h"
#include "search.h"


bool checkClosedSize(List *list);
bool checkFringeSize(List *list);
char *stateToString(StateNode *state);
void deleteFringeNode(FringeNode *fn);

List *newFringe(void)
{
    List* fringe = (List *) malloc(sizeof(List));

    FringeNode **items = (FringeNode **) malloc(sizeof(FringeNode*) * 32);
    fringe->items = items;
    fringe->capacity = 32;
    fringe->n_items = 0;

    return fringe;
}

void deleteFringe(List *fringe)
{
    FringeNode **items = (FringeNode **)fringe->items;
    for (int i = 0; i < fringe->n_items; i += 1)
    {
        FringeNode *fn = (FringeNode *)items[i];
        free(fn->state->location);
        free(fn->state);
        free(fn->allActions);
        free(fn);
    }
    free(items);
    free(fringe);
}

FringeNode *popFromFringe(List *fringe)
{
    if (fringe->n_items < 1)
    {
        return NULL;

    } else {

        // get list of pointers
        FringeNode **items = (FringeNode **)fringe->items;
        
        // grab pointer to last item
        FringeNode *fn = (FringeNode *)items[fringe->n_items - 1];

        // decriment count of items
        fringe->n_items -= 1;

        // eliminate pointer from list
        items[fringe->n_items] = NULL;
        
        // return pointer    
        return fn;
    }
}

void addToFringe(FringeNode *fn, List *fringe)
{
    if (checkFringeSize(fringe))
    {
        FringeNode **items = (FringeNode **) fringe->items;
        items[fringe->n_items] = fn;
        fringe->items = items;
        fringe->n_items += 1; 
    }
}

HashTable *newClosed(void)
{
    HashTable *closed = newHashTable();
    return closed;
}

void deleteClosed(HashTable *closed)
{
    deleteHashTable(closed);
}

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

// accepts the new state, and the old fringenode's allActions and costOfActions
FringeNode *newFringeNode(StateNode *state, char *pastActions, int pastCost)
{
    int len = strlen(pastActions);
    char* allActions = malloc((len + 2)); // pastActions + new action + '\0'
    int i = 0;
    while (i < len)
    {
        allActions[i] = pastActions[i]; 
        i += 1; 
    }
    allActions[len] = state->action;
    allActions[len + 1] = '\0';

    int costOfActions = pastCost + state->cost;

    FringeNode *fn = (FringeNode *) malloc(sizeof(FringeNode));    

    fn->state = state;
    fn->allActions = allActions;
    fn->costOfActions = costOfActions;
   
    return fn;
}

void deleteFringeNode(FringeNode *fn)
{
    deleteStateNode(fn->state);
    free(fn->allActions);
    free(fn);
}

char *dfs (Game *game)
{
    /*
    printf("Depth First Search working...\n");
    int md = manhattanDistance(game->start->x, game->start->y, game->goal->x, game->goal->y);
    printf("Manhattan distance from start to goal: %d\n", md);
    */

    List *fringe = newFringe();
    
    HashTable *closed = newClosed();

    StateNode *startState = (StateNode *) malloc(sizeof(StateNode));
    Location *l = malloc(sizeof(Location));
    l->x = game->start->x;
    l->y = game->start->y;
    startState->location = l;
    startState->action = 0;
    startState->cost = 0;
   
    char *startPath = "\0";
    int startCost = 0;
    FringeNode *first = newFringeNode(startState, startPath, startCost);

    addToFringe(first, fringe);

    long expanded = 0;
    long total_fringe = 0;
    long average_fringe = 0;
    
    while(true)
    {
        FringeNode *thisNode = popFromFringe(fringe);

        if (thisNode == NULL)
        {
            printf("No Solution found :(\n");

            deleteFringe(fringe);
            deleteClosed(closed);

            return NULL;
        } 

        expanded += 1;
        total_fringe += fringe->n_items;
        average_fringe = total_fringe / expanded;

        if (sameLocation(thisNode->state->location->x, thisNode->state->location->y, game->goal->x, game->goal->y))
        {

            int len = strlen(thisNode->allActions);
            char *pathToVictory = malloc(len + 1);

            for (int i = 0; i <= len; i += 1)
            {
                pathToVictory[i] = thisNode->allActions[i];
            }

            int totalCost = thisNode->costOfActions;
            
            free(thisNode->state->location);
            free(thisNode->state);
            free(thisNode->allActions);
            free(thisNode);

            deleteFringe(fringe);
            deleteClosed(closed);

            printf("Total movement cost of solution: %d\n", totalCost);
            printf("Total locations explored: %ld\n", expanded);
            printf("Average number of locations stored: %ld\n", average_fringe);

            return pathToVictory;

        } else {
            
            char *pastActions = thisNode->allActions;
            int pastCost = thisNode->costOfActions;

            List *successors = getSuccessorStateNodes(thisNode->state, game->board);

            StateNode **items = successors->items;
            int len = successors->n_items;
            for (int i = 0; i < len; i += 1)
            {
                StateNode *successor = items[i];
                
                if (!inClosed(successor, closed))
                {
                    addToClosed(successor, closed);
                    FringeNode *fn = newFringeNode(successor, pastActions, pastCost);
                    addToFringe(fn, fringe);
                }
            }
            
            free(items); 
            free(successors);

            free(thisNode->state->location);
            free(thisNode->state);
            free(thisNode->allActions);
            free(thisNode);
        }
    } 
}

bool checkClosedSize(List *list)
{
    if (list->n_items >= list->capacity) 
    {
        int new_size = list->capacity * 2;
        
        Location **items = (Location**) list->items;
        items = realloc(items, sizeof(Location*) * new_size);

        if (items == NULL) 
        {
            return false;
        }

        list->items = items;
        list->capacity = new_size; 
    }
    return true;
}

bool checkFringeSize(List *list)
{
    if (list->n_items >= list->capacity) 
    {
        int new_size = list->capacity * 2;
        
        FringeNode **items = (FringeNode**) list->items;
        
        items = realloc(items, sizeof(FringeNode*) * new_size);

        if (items == NULL) 
        {
            return false;
        }

        list->items = items;
        list->capacity = new_size; 
    }
    return true;
}

char *stateToString(StateNode *state)
{
    char * sh = malloc(sizeof(char) * 5);

    sh[0] = state->location->x + 48;
    sh[1] = state->location->y + 48;
    sh[2] = state->action;
    sh[3] = state->cost + 48;
    sh[4] = '\0';
    
    return sh; 
}
