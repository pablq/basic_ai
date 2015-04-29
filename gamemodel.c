#include <stdlib.h>
#include "gamemodel.h"
#include "grid.h"
#include "location.h"
#include "list.h"

// returns a string of legal actions from a given location on the gameboard
char *getLegalActions(Location *loc, Grid board)
{
    int x = loc-> x;
    int y = loc-> y; 

    bool n = isLegal(x,y - 1, board);
    bool s = isLegal(x,y + 1, board);
    bool e = isLegal(x + 1,y, board);
    bool w = isLegal(x - 1,y, board);

    // max length is 4 actions.
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

// used to store states in closed set hashtable
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

// gets cost on board for a given location
// should only ever return 1, 2, or 4
int costFn(Location *loc, Grid board)
{
    int val = board[loc->x][loc->y];
    return val;
}

// called in search algorithms to get successor states from a given state
List *getSuccessorStateNodes(StateNode *parent, Grid board) 
{
    // list will never be greater than 4 items (n,s,e,w)
    List* successors = malloc(sizeof(List));
    StateNode **items = malloc(sizeof(StateNode *) * 4);
    successors->items = items;
    successors->nItems = 0;
    successors->capacity = 4; 

    char *actions = getLegalActions(parent->loc, board);
    
    int i = 0;
    while (actions[i] != '\0')
    {
        char action = actions[i];

        int nextX, nextY;

        switch (action) 
        {
            case 'n':
                nextX = parent->loc->x;
                nextY = parent->loc->y - 1;
                break;
            case 's':
                nextX = parent->loc->x;
                nextY = parent->loc->y + 1;
                break;
            case 'e': 
                nextX = parent->loc->x + 1;
                nextY = parent->loc->y;
                break;
            case 'w':
                nextX = parent->loc->x - 1;
                nextY = parent->loc->y;
                break;
        }

        Location *loc = malloc(sizeof(Location));
        loc->x = nextX;
        loc->y = nextY;

        StateNode *s = malloc(sizeof(StateNode));
        s->loc = loc;
        s->cost = costFn(loc, board);
        s->action = action;

        StateNode **list = (StateNode **) successors->items;
        list[i] = s;
        successors->items = list;

        i += 1;
        successors->nItems = i;
    }
    free(actions);

    return successors;
}
