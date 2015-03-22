#ifndef LOCATION 
#define LOCATION
#include "location.h"
#endif

#ifndef GRID
#define GRID
#include "grid.h"
#endif

#ifndef BOOL
#define BOOL
#include <stdbool.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

char *getLegalActions(Location *agent, Grid *grid)
{
    bool n = *grid[agent->x][agent->y - 1] != 'X' ? true : false;
    bool s = *grid[agent->x][agent->y + 1] != 'X' ? true : false;
    bool e = *grid[agent->x + 1][agent->y] != 'X' ? true : false;
    bool w = *grid[agent->x - 1][agent->y] != 'X' ? true : false;

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
