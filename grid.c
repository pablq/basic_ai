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
    // this is the basic build. it just populates the outside with walls
    for (int x = 0; x < WIDTH; x += 1) 
    {
        for (int y = 0; y < HEIGHT; y += 1) 
        {
            if ((y == 0 || y == HEIGHT - 1) || (x == 0 || x == WIDTH - 1))
            {
                *grid[x][y] = 'X';
            } else {
                *grid[x][y] = ' ';
            }
        }
    }

    // Add some interior walls
    int num_walls = randInRange(15,30);
    for (int i = 0; i < num_walls; i += 1)
    {
        int x, y, is_horiz, len = randInRange(2,5);

        is_horiz = randInRange(0,1);
        if(is_horiz) 
        {
            x = randInRange(1, WIDTH - (len + 1)); // we avoid overlap with border wall and out of bounds error
            y = randInRange(6, HEIGHT - 6); // make sure there are at least 5 spaces between wall and border wall
    
        } else {
            x = randInRange(6, WIDTH - 6);
            y = randInRange(1, HEIGHT - (len + 1));
        }

        for (int j = 0; j < len; j += 1)
        {
            *grid[x][y] = 'X';
            if (is_horiz) {
                if ((j > 0 && j < len - 1) && (*grid[x][y+1] == 'X' || *grid[x][y-1] == 'X'))
                {
                    break;
                } else {
                    x += 1;
                }
            } else {
                if ((j > 0 && j < len - 1) && (*grid[x+1][y] == 'X' || *grid[x][x-1] == 'X'))
                {
                    break;
                } else {
                    y += 1;
                }
            }
        }
    }
}

void printGrid(Grid *grid)
{
    for (int y = 0; y < HEIGHT; y += 1) 
    {
        for (int x = 0; x < WIDTH; x += 1) 
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
        int x = randInRange(0,WIDTH - 1);
        int y = randInRange(0,HEIGHT - 1);

        if (*grid[x][y] != 'X' && *grid[x][y] != 'G')
        {
            *grid[x][y] = 'A';

            agent->x = x;
            agent->y = y;
            placed += 1;
            printf("placed agent at %d,%d\n",x,y);
        }
    }
}

void placeGoal(Location *goal, Grid *grid)
{
    int placed = 0;
    while (!placed)
    {
        int x = randInRange(0,WIDTH - 1);
        int y = randInRange(0,HEIGHT - 1);

        if (*grid[x][y] != 'X' && *grid[x][y] != 'A')
        {
            *grid[x][y] = 'G';

            goal->x = x;
            goal->y = y;
            placed += 1;
            printf("placed goal at %d,%d\n",x,y);
        }
    }
}
