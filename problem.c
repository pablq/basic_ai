#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "location.h"
#include "grid.h"
#include "list.h"
#include "problem.h"

/*
 * ACTION STRINGS MUST *ALWAYS* BE NULL-TERMINATED
 *
 */

Location *getNeighbor(char action, Location *old, Location *new);

void deleteNode(Node *node);

char *getLegalActions(Location *loc, Grid *board, char *moves);

int costFn(Location *location, Grid *board);

// if the costFn is passed a wall it will give a favorable value!
// you should check for the legality of a location before calling the costfn
int costFn(Location *location, Grid *board)
{
    return *board[location->x][location->y];
}

// TODO
Node *getFirstNode(Node *node, Grid *board)
{
    return node;
}

// this function is exposed in the api.
// a search algorithem will call this to get the neighboring 'state's to a given parent node.
// this function assumes successors->list has 4 available slots for Nodes.
List *getSuccessors(List *successors, Node *parent, Grid *board) 
{
    char legalActions[5]; // space for four moves + a null terminator
    getLegalActions(parent->location, board, legalActions);
    
    int i = 0;
    while (legalActions[i] != '\0')
    {
        char action = legalActions[i];

        Node *successor = (Node *)malloc(sizeof(Node));

        Location *s_location = malloc(sizeof(Location));

        successor->location = getNeighbor(action, parent->location, s_location);
        successor->cost = costFn(successor->location, board);
        successor->action = action;

        Node **list = (Node **) successors->list;
        list[i]= successor;

        successors->length = i;
        i += 1;
    }

    return successors;
}


// helper function for getSuccessors
Location *getNeighbor(char action, Location *old, Location *new)
{
    int new_x, new_y;
    int x = old->x;
    int y = old->y;

    switch (action) 
    {
        case 'n':
            new_x = x;
            new_y = y - 1;
            break;
        case 's':
            new_x = x;
            new_y = y + 1;
            break;
        case 'e': new_x = x + 1;
            new_y = y;
            break;
        case 'w':
            new_x = x - 1;
            new_y = y;
            break;
        default:
            return NULL;
    }

    new->x = new_x;
    new->y = new_y;

    return new;
}

void deleteNode(Node *node)
{
    free(node->location);
    free(node);
}

char *getLegalActions(Location *loc, Grid *board, char *moves)
{
    bool n = isLegal(loc->x, loc->y - 1, board);
    bool s = isLegal(loc->x, loc->y + 1, board);
    bool e = isLegal(loc->x + 1, loc->y, board);
    bool w = isLegal(loc->x - 1, loc->y, board);

    int total_moves = 0;
    if (n) {
        moves[total_moves] = 'n';
        total_moves += 1;
    }
    if (s) {
        moves[total_moves] = 's';
        total_moves += 1;
    }
    if (e) {
        moves[total_moves] = 'e';
        total_moves += 1;
    }
    if (w) {
        moves[total_moves] = 'w';
        total_moves += 1;
    }
    moves[total_moves] = '\0';

    return moves;
}

// THIS FUNCTION IS NO LONGER ANY GOOD.
// WE NEED EITHER THE GAME, OR THE GAME'S GOAL LOCATION.
// PASSING A COPY OF THE GAME SEEMS TO ME TO BE A REASONABLE
// THING TO DO AS THE AI METHODS WILL NOT MODIFY IT
// AND THERE ISN'T A WHOLE LOT OF DATA TO COPY OVER
bool checkForWin(Location *location, Grid *board)
{
    if (*board[location->x][location->y] == 'G')
    {
        return true;
    } else {
        return false;
    }
}
