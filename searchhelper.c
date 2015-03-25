#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "location.h"
#include "grid.h"
#include "game.h"
#include "list.h"
#include "problem.h"

/*
 * ACTION STRINGS MUST *ALWAYS* BE NULL-TERMINATED
 *
 */

Location *getNeighbor(char action, Location *old, Location *new);

void deleteStateNode(StateNode *node);

char *getLegalActions(Location *loc, Grid *board, char *moves);

int costFn(Location *location, Grid *board);

// if the costFn is passed a wall it will give a favorable value!
// you should check for the legality of a location before calling the costfn
int costFn(Location *location, Grid *board)
{
    return *board[location->x][location->y];
}

StateNode *getFirstStateNode(StateNode *first, Game *game)
{
    // location must be malloc'd already!
    first->location = game->start;
    first->cost = 0;
    first->action = 0;

    return first;
}

// this function is exposed in the api.
// a search algorithem will call this to get the neighboring 'state's to a given parent node.
// this function assumes successors->list has 4 available slots for StateNodes.
List *getSuccessors(List *successors, StateNode *parent, Grid *board) 
{
    char legalActions[5]; // space for four moves + a null terminator
    getLegalActions(parent->location, board, legalActions);
    
    int i = 0;
    while (legalActions[i] != '\0')
    {
        char action = legalActions[i];

        StateNode *successor = (StateNode *)malloc(sizeof(StateNode));

        Location *s_location = malloc(sizeof(Location));

        successor->location = getNeighbor(action, parent->location, s_location);
        successor->cost = costFn(successor->location, board);
        successor->action = action;

        StateNode **list = (StateNode **) successors->list;
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

void deleteStateNode(StateNode *node)
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

bool checkForWin(Location *location, Game *game)
{
    return sameLocation(location->x, location->y, game->goal->x, game->goal->y);
}
