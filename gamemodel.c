#include <stdlib.h>
#include "gamemodel.h"
#include "grid.h"
#include "location.h"
#include "list.h"

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


// STATE SPECIFIC BELOW

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

// this function is exposed in the api.
// a search algorithem will call this to get the neighboring 'state's to a given parent node.
List *getSuccessorStateNodes(StateNode *parent, Grid board) 
{
    List* successors = (List *) malloc(sizeof(List));
    StateNode **items = (StateNode **) malloc(sizeof(StateNode *) * 4);
    successors->items = items;
    successors->n_items = 0;
    successors->capacity = 4; 

    char *actions = getLegalActions(parent->location, board);
    
    int i = 0;
    while (actions[i] != '\0')
    {
        char action = actions[i];

        int next_x, next_y;

        switch (action) 
        {
            case 'n':
                next_x = parent->location->x;
                next_y = parent->location->y - 1;
                break;
            case 's':
                next_x = parent->location->x;
                next_y = parent->location->y + 1;
                break;
            case 'e': 
                next_x = parent->location->x + 1;
                next_y = parent->location->y;
                break;
            case 'w':
                next_x = parent->location->x - 1;
                next_y = parent->location->y;
                break;
        }

        Location *location = malloc(sizeof(Location));
        location->x = next_x;
        location->y = next_y;

        StateNode *successor = malloc(sizeof(StateNode));
        successor->location = location;
        successor->cost = 1;
        successor->action = action;

        StateNode **list = (StateNode **) successors->items;
        list[i] = successor;
        successors->items = list;

        i += 1;
        successors->n_items = i;
    }
    
    free(actions);
    
    trimListSize(successors);

    return successors;
}
