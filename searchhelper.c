#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "location.h"
#include "grid.h"
#include "game.h"
#include "list.h"
#include "searchhelper.h"

/*
 * ACTION STRINGS MUST *ALWAYS* BE NULL-TERMINATED
 *
 */

Location *getNeighbor(char action, Location *location);

StateNode *newStateNode(void);

void deleteStateNode(StateNode *sn);

char *getLegalActions(Location *loc, Grid board);

// if the costFn is passed a wall it will give a favorable value!
// you should check for the legality of a location before calling the costfn
int costFn(Location *location, Grid board)
{
    int val = board[location->x][location->y];
    return val;
}

StateNode *getFirstStateNode(int x, int y)
{
    StateNode *first = newStateNode();

    first->location->x = x;
    first->location->y = y;
    first->action = 0;
    first->cost = 0;

    return first;
}

StateNode* newStateNode(void)
{
    StateNode *sn = (StateNode *) malloc(sizeof(StateNode));
    sn->location = NULL;
    sn->action = 0;
    sn->cost = 0;

    return sn;
}

void deleteStateNode(StateNode *sn)
{
    free(sn->location);
    free(sn);
}

List* new4StateNodesList(void)
{
    List* n4sn = (List *) malloc(sizeof(List));
    
    StateNode **items = (StateNode **) malloc(sizeof(StateNode *) * 4);

    n4sn->items = items;
    n4sn->n_items = 0;
    n4sn->capacity = 4; 

    return n4sn;
}

// this function is exposed in the api.
// a search algorithem will call this to get the neighboring 'state's to a given parent node.
List *getSuccessorStateNodes(StateNode *parent, Grid board) 
{
    List *successors = new4StateNodesList();

    char *actions = getLegalActions(parent->location, board);
    
    int i = 0;
    while (actions[i] != '\0')
    {
        char action = actions[i];

        StateNode *successor = malloc(sizeof(StateNode));

        successor->location = getNeighbor(action, parent->location);
        successor->cost = 1;
        successor->action = action;

        StateNode **list = (StateNode **) successors->items;
        list[i] = successor;
        successors->items = list;

        i += 1;
        successors->n_items = i;
    }
    
    free(actions);
    
    // trimListSize(successors);

    return successors;
}

// helper function for getSuccessors
Location *getNeighbor(char action, Location *location)
{
    int neighbor_x, neighbor_y;
    int x = location->x;
    int y = location->y;

    switch (action) 
    {
        case 'n':
            neighbor_x = x;
            neighbor_y = y - 1;
            break;
        case 's':
            neighbor_x = x;
            neighbor_y = y + 1;
            break;
        case 'e': 
            neighbor_x = x + 1;
            neighbor_y = y;
            break;
        case 'w':
            neighbor_x = x - 1;
            neighbor_y = y;
            break;
        default:
            return NULL;
    }

    Location *neighbor = malloc(sizeof(Location));
    neighbor->x = neighbor_x;
    neighbor->y = neighbor_y;

    return neighbor;
}

char *getLegalActions(Location *loc, Grid board)
{
    int x = loc-> x;
    int y = loc-> y; 

    bool n = isLegal(x, y - 1, board);
    bool s = isLegal(x, y + 1, board);
    bool e = isLegal(x + 1, y, board);
    bool w = isLegal(x - 1, y, board);

    char *actions = (char *) malloc(sizeof(char) * 5);

    int total_moves = 0;
    if (n) {
        actions[total_moves] = 'n';
        total_moves += 1;
    }
    if (s) {
        actions[total_moves] = 's';
        total_moves += 1;
    }
    if (e) {
        actions[total_moves] = 'e';
        total_moves += 1;
    }
    if (w) {
        actions[total_moves] = 'w';
        total_moves += 1;
    }
    actions[total_moves] = '\0';

    return actions;
}
