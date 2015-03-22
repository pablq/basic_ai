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

void buildLayout(Grid *grid)
{
    for (int x = 0; x < WIDTH; x++) 
    {
        for (int y = 0; y < HEIGHT; y++) 
        {
            if ((y == 0 || y == HEIGHT - 1) || (x == 0 || x == WIDTH - 1))
            {
                *grid[x][y] = 'X';
            } else {
                *grid[x][y] = ' ';
            }
        }
    }

    int placed = 0;
    while (placed < 2)
    {
        int place_x = randInRange(1, WIDTH - 1);
        int place_y = randInRange(1, HEIGHT - 1);

        printf("x:%d,y:%d\n",place_x,place_y);

        // first we'll set agent
        if (placed == 0)
        {
            *grid[place_x][place_y] = 'A';
            placed += 1;
        } else {
            // make sure the new place isn't agent's place
            if (*grid[place_x][place_y] != 'A')
            {
                *grid[place_x][place_y] = 'G';
                placed += 1;
            }
        }
    }
}

void printGrid(Grid *grid)
{
    for (int y = 0; y < HEIGHT; y++) 
    {
        for (int x = 0; x < WIDTH; x++) 
        {
            printf("%c", *grid[x][y]);
        }
        printf("\n");
    }
}

void placeAgent(Location *agent, Grid *grid)
{
    int placed = 0;
    while (!placed)
    {
        int x = randInRange(0,WIDTH);
        int y = randInRange(0,HEIGHT);

        if (*grid[x][y] != 'X' && *grid[x][y] != 'G')
        {
            *grid[x][y] = 'A';

            agent->x = x;
            agent->y = y;
            placed += 1;
        }
    }
}

void placeGoal(Location *goal, Grid *grid)
{
    int placed = 0;
    while (!placed)
    {
        int x = randInRange(0,WIDTH);
        int y = randInRange(0,HEIGHT);

        if (*grid[x][y] != 'X' && *grid[x][y] != 'A')
        {
            *grid[x][y] = 'G';

            goal->x = x;
            goal->y = y;
            placed += 1;
        }
    }
}
