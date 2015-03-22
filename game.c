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

bool moveAgent(char dir, Grid *grid);

int main(void)
{
    Grid *grid = malloc(sizeof(Grid));
    buildLayout(grid);

    Location *agent = malloc(sizeof(Location));
    placeAgent(agent, grid);

    Location *goal = malloc(sizeof(Location));
    placeGoal(goal, grid);

    printGrid(grid);

    char dirs[7] = { 'N','S','E','W','4','T','5' };
    for (int i = 0; i < 7; i += 1)
    {
        char dir = dirs[i];
        if (moveAgent(dir, grid)) {
            printf("%c\n", dir);
        } else {
            printf("NOT A DIRECTION\n");
        }

    }

    free(grid);
    free(agent);
    free(goal);
}

bool moveAgent(char dir, Grid *grid)
{
    switch (dir)
    {
        case 'N':
            break;
        case 'S':
            break;
        case 'E':
            break;
        case 'W':
            break;
        default:
            return false;
    }

    return true;
}
