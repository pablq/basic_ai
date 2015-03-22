#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
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

#ifndef BOOL
#define BOOL
#include <stdbool.h>
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

    // Add some interior walls:
    
    int num_walls = randInRange(15,30);
    for (int i = 0; i < num_walls; i += 1)
    {
        int len = randInRange(2,5);
        int x, y;

        // decide whether wall will be horizontal or vertical.
        // we'll draw the wall by either incrementing y or x depending on
        // whether the wall is horizontal or vertical. so, we have to make 
        // sure we save enough space to not overwrite the array
        // also, we make sure a wall that is parallel to the outside wall
        // has at least a buffer of 1 space
        int is_horiz = randInRange(0,1);
        if(is_horiz) 
        {
            x = randInRange(1, WIDTH - (len + 1));
            y = randInRange(2, HEIGHT - 3);
    
        } else {
            x = randInRange(2, WIDTH - 3);
            y = randInRange(2, HEIGHT - (len + 1));
        }

        // here we actually draw the wall
        for (int j = 0; j < len; j += 1)
        {
            // draw the wall!
            *grid[x][y] = 'X';
            if (is_horiz) { // for horizontal walls
                // if the next block is already an 'X' or there is an 'X' above or below, we're done with this wall
                if ((j > 0 && j < len - 1) && (*grid[x+1][y] == 'X' || *grid[x][y+1] == 'X' || *grid[x][y-1] == 'X'))
                {
                    break;
                } else { // otherwise, advance to the next block
                    x += 1;
                }
            } else { // for vertical walls
                // if the next block is already an 'X' or there is an 'X' to the right or left, we're done with this wall
                if ((j > 0 && j < len - 1) && (*grid[x+1][y] == 'X' || *grid[x][x-1] == 'X'))
                {
                    break;
                } else { // otherwise, advance to the next block
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
    bool placed = false;
    while (!placed)
    {
        int x = randInRange(0,WIDTH - 1);
        int y = randInRange(0,HEIGHT - 1);

        if (*grid[x][y] != 'X' && *grid[x][y] != 'G')
        {
            *grid[x][y] = 'A';

            agent->x = x;
            agent->y = y;
            placed = true;
        }
    }
}

void placeGoal(Location *goal, Grid *grid)
{
    bool placed = false;
    while (!placed)
    {
        int x = randInRange(0,WIDTH - 1);
        int y = randInRange(0,HEIGHT - 1);

        if (*grid[x][y] != 'X' && *grid[x][y] != 'A')
        {
            *grid[x][y] = 'G';
            goal->x = x;
            goal->y = y;
            placed = true;
        }
    }
}
