#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef GAME_STRUCTS
#define GAME_STRUCTS
#include "game_structs.h"
#endif

#ifndef FUNCS
#define FUNCS
#include "funcs.h"
#endif

#ifndef WH
#define WH
#define WIDTH 50
#define HEIGHT 25
#endif

#ifndef GRID
#define GRID
#include "grid.h"
#endif

#ifndef LOCATION
#define LOCATION
#include "location.h"
#endif

#ifndef STDBOOL
#define STDBOOL
#include <stdbool.h>
#endif

#ifndef PROBLEM
#define PROBLEM
#include "problem.h"
#endif

void drawPath(char *actions, Location *start, Grid *grid);
bool checkForWin(Location *location, Grid *grid);
Location *getNextLocation(char action, Location *start, Grid *grid);

int main(void)
{
    Grid *grid = malloc(sizeof(Grid));
    buildLayout(grid);

    Location *agent = malloc(sizeof(Location));
    placeAgent(agent, grid);

    Location *goal = malloc(sizeof(Location));
    placeGoal(goal, grid);

    printGrid(grid);

    drawPath("NSSE", agent, grid);

    /*
    char *moves = getLegalActions(agent, grid);
    int total_moves = 0;
    if (moves != NULL)
    {
        while(moves[total_moves] != '\0')
        {
            total_moves += 1;
        }
    }
    printf("total moves; %d\n", total_moves);

    */

    // free(moves);
    free(grid);
    free(agent);
    free(goal);
}

Location *getNextLocation(char action, Location *start, Grid *grid)
{
    int new_x, new_y;
    int x = start->x;
    int y = start->y;
    switch (action) {
        case 'N':
            new_x = x;
            new_y = y - 1;
            break;
        case 'S':
            new_x = x;
            new_y = y + 1;
            break;
        case 'E':
            new_x = x + 1;
            new_y = y;
            break;
        case 'W':
            new_x = x - 1;
            new_y = y;
            break;
        default:
            return NULL;
    }

    // note that we create a new struct and return it.
    // WE DO NOT FREE THE OLD STRUCT HERE
    Location *nextLocation = malloc(sizeof(Location));
    nextLocation->x = new_x;
    nextLocation->y = new_y;
    return nextLocation;
}


void drawPath(char *actions, Location *start, Grid *grid)
{
    Location *last = malloc(sizeof(Location));
    last->x = start->x;
    last->y = start->y;

    int i = 0;
    while(actions[i] != '\0')
    {
        char action = actions[i];
        Location *next = getNextLocation(action, last, grid);
        if (next != NULL)
        {
            *grid[next->x][next->y] = '%';
        }
        free(last);
        last = next;
    }
    free(last);
}
        
