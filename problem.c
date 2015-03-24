#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "location.h"
#include "grid.h"
#include "list.h"
#include "problem.h"

/*
 * NOTE TO SELF:
 * COMBINE GETSUCCESSOR AND GETLEGALACTIONS.
 * THE NEW FUNCTION WILL RETURN AN ARRAY OF SUCCESSORS
 * THE THING TO CONSIDER NOW, IS HOW WILL WE KNOW EXACTLY HOW MANY SUCCESSORS THERE WERE?
 * PERHAPS I CAN MAKE THE PATH STRUCT MORE GENERIC.
 * IT WILL HOLD A VOID* AND INT FOR THE NUMBER OF ITEMS ASSOCIATED WITH IT.
 * I STILL HAVE TO CONSIDER HOW TO COUNT THE LENGTH OF ACTION STRINGS...
 * IF THEY ARE REGULAR STRINGS THEN I'LL HAVE TO COUNT THEM EVERY TIME I PASS THEM TO ANYTHING.
 * OR, I CAN HAVE THEM BE STORED IN THE ABOVE GENERIC { VOID*; INT } STRUCT
 * RIGHT NOW I THINK IT'D BE EASIER TO USE PLAIN STRINGS AND EITHER STRLEN
 * OR WRITE MY OWN LAME STRING COUNTING FUNCTION. <- IF I DO WRITE MY OWN I'LL HAVE TO
 * BE QUITE CAREFUL TO MAKE SURE THE STRINGS ARE *ALWAYS* NULL-TERMINATED.
 *
 */

Location *getNeighbor(char action, Location *old, Location *new);

void deleteNode(Node *node);

char *getLegalActions(Location *loc, Grid *grid);

int costFn(Location *location, Grid *grid);

int costFn(Location *location, Grid *grid)
{
    return 1;
}

Node *getFirstNode(Node *node, Grid *grid)
{
    return node;
}

List *getSuccessors(List *successors, Node *parent, Grid *grid) // this function assumes successors->list has 4 available slots.
{
    char *legalActions = getLegalActions(parent->location, grid);
    
    int i = 0;
    while (legalActions[i] != '\0')
    {
        char action = legalActions[i];

        Node *successor = (Node *)malloc(sizeof(Node));

        Location *s_location = malloc(sizeof(Location));

        successor->location = getNeighbor(action, parent->location, s_location);
        successor->cost = costFn(successor->location, grid);
        successor->action = action;

        Node **list = (Node **) successors->list;
        list[i]= successor;

        successors->length = i;
        i += 1;
    }

    return successors;
}


// must check for null.
Location *getNeighbor(char action, Location *old, Location *new)
{
    int new_x, new_y;
    int x = old->x;
    int y = old->y;

    switch (action) 
    {
        case 'N':
            new_x = x;
            new_y = y - 1;
            break;
        case 'S':
            new_x = x;
            new_y = y + 1;
            break;
        case 'E': new_x = x + 1;
            new_y = y;
            break;
        case 'W':
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

// note this function mallocs a char *!!
char *getLegalActions(Location *loc, Grid *grid)
{
    bool n = *grid[loc->x][loc->y - 1] != 'X' ? true : false;
    bool s = *grid[loc->x][loc->y + 1] != 'X' ? true : false;
    bool e = *grid[loc->x + 1][loc->y] != 'X' ? true : false;
    bool w = *grid[loc->x - 1][loc->y] != 'X' ? true : false;

    char *moves = malloc(sizeof(char) * 5); // we will null terminate the string with max length of 4

    int total_moves = 0;
    if (n) {
        moves[total_moves] = 'N';
        total_moves += 1;
    }
    if (s) {
        moves[total_moves] = 'S';
        total_moves += 1;
    }
    if (e) {
        moves[total_moves] = 'E';
        total_moves += 1;
    }
    if (w) {
        moves[total_moves] = 'W';
        total_moves += 1;
    }
    if (total_moves == 0) 
    {
        free(moves);
        return NULL;
    } else {
        moves[total_moves] = '\0';
        return moves;
    }
}

bool checkForWin(Location *location, Grid *grid)
{
    if (*grid[location->x][location->y] == 'G')
    {
        return true;
    } else {
        return false;
    }
}
