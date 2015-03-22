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

Location *moveAgent(char dir, Location *start, Grid *grid);
bool checkForWin(Location *location, Grid *grid);

int main(void)
{
    Grid *grid = malloc(sizeof(Grid));
    buildLayout(grid);

    Location *agent = malloc(sizeof(Location));
    placeAgent(agent, grid);

    Location *goal = malloc(sizeof(Location));
    placeGoal(goal, grid);

    printGrid(grid);

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

    while 
    
    /*
    if (moves != NULL)
    {
        char move = 'X';
        int index = 0;
        while (moves[index] != '\0')
        {
            move = moves[index];
            printf("%c,%d\n",move,index);
            if (moveAgent(move, grid)) {
                printf("%c\n", move);
            } else {
                printf("NOT A DIRECTION\n");
            }
            index += 1;
        }
    }
    */

    free(moves);
    free(grid);
    free(agent);
    free(goal);
}

Location *moveAgent(char dir, Location *start, Grid *grid)
{
    int new_x, new_y;
    int x = start->x;
    int y = start->y;
    char mark;
    switch (dir)
    {
        case 'N':
            new_x = x;
            new_y = y - 1;
            mark = '^';
            break;
        case 'S':
            new_x = x;
            new_y = y + 1;
            mark = 'v';
            break;
        case 'E':
            new_x = x + 1;
            new_y = y;
            mark = '>';
            break;
        case 'W':
            new_x = x - 1;
            new_y = y;
            mark = '<';
            break;
        default:
            return NULL;
    }

    Location *new = malloc(sizeof(Location));
    new-> x = new_x;
    new-> y = new_y;

    if (checkForWin(new, grid))
    {
        *grid[new->x][new->y] = 'O'; 
        printf("WIN!!!\n");
    } else {
        *grid[new->x][new->y] = mark; 
    }

    free(start);

    return new;
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
