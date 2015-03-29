#include <stdlib.h>
#include "gamemodel.h"
#include "grid.h"
#include "location.h"
#include "list.h"

int costFn(Location *loc, Grid board)
{
    int val = board[loc->x][loc->y];
    return val;
}

char *getLegalActions(Location *loc, Grid board)
{
    int x = loc-> x;
    int y = loc-> y; 

    bool n = isLegal(x, y - 1, board);
    bool s = isLegal(x, y + 1, board);
    bool e = isLegal(x + 1, y, board);
    bool w = isLegal(x - 1, y, board);

    char *actions = malloc(sizeof(char) * 5);

    int i = 0;
    if (n) {
        actions[i] = 'n';
        i += 1;
    }
    if (s) {
        actions[i] = 's';
        i += 1;
    }
    if (e) {
        actions[i] = 'e';
        i += 1;
    }
    if (w) {
        actions[i] = 'w';
        i += 1;
    }
    actions[i] = '\0';

    return actions;
}


// STATE SPECIFIC BELOW

char *stateToString(StateNode *state)
{
    char *sh = malloc(sizeof(char) * 5);

    sh[0] = state->loc->x;
    sh[1] = state->loc->y;
    sh[2] = state->action;
    sh[3] = state->cost + 48;
    sh[4] = '\0';
    
    return sh; 
}

// this function is exposed in the api.
// a search algorithem will call this to get the neighboring 'state's to a given parent node.
List *getSuccessorStateNodes(StateNode *parent, Grid board) 
{
    List* successors = malloc(sizeof(List));
    StateNode **items = malloc(sizeof(StateNode *) * 4);
    successors->items = items;
    successors->n_items = 0;
    successors->capacity = 4; 

    char *actions = getLegalActions(parent->loc, board);
    
    int i = 0;
    while (actions[i] != '\0')
    {
        char action = actions[i];

        int next_x, next_y;

        switch (action) 
        {
            case 'n':
                next_x = parent->loc->x;
                next_y = parent->loc->y - 1;
                break;
            case 's':
                next_x = parent->loc->x;
                next_y = parent->loc->y + 1;
                break;
            case 'e': 
                next_x = parent->loc->x + 1;
                next_y = parent->loc->y;
                break;
            case 'w':
                next_x = parent->loc->x - 1;
                next_y = parent->loc->y;
                break;
        }

        Location *loc = malloc(sizeof(Location));
        loc->x = next_x;
        loc->y = next_y;

        StateNode *s = malloc(sizeof(StateNode));
        s->loc = loc;
        s->cost = costFn(loc, board);
        s->action = action;

        StateNode **list = (StateNode **) successors->items;
        list[i] = s;
        successors->items = list;

        i += 1;
        successors->n_items = i;
    }
    
    free(actions);
    
    return successors;
}
