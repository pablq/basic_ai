#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef GRID_DIMS
#define GRID_DIMS
#define GRID_WIDTH 50
#define GRID_HEIGHT 25
#endif

#ifndef GRID
#define GRID
#include "grid.h"
#endif

#ifndef UTIL
#define UTIL
#include "util.h"
#endif

void buildLayout(Grid *grid)
{
    // this is the basic build. it just populates the outside with walls
    for (int x = 0; x < GRID_WIDTH; x += 1) 
    {
        for (int y = 0; y < GRID_HEIGHT; y += 1) 
        {
            if ((y == 0 || y == GRID_HEIGHT - 1) || (x == 0 || x == GRID_WIDTH - 1))
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
            x = randInRange(1, GRID_WIDTH - (len + 1));
            y = randInRange(2, GRID_HEIGHT - 3);
    
        } else {
            x = randInRange(2, GRID_WIDTH - 3);
            y = randInRange(2, GRID_HEIGHT - (len + 1));
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
    for (int y = 0; y < GRID_HEIGHT; y += 1) 
    {
        for (int x = 0; x < GRID_WIDTH; x += 1) 
        {
            printf("%c", *grid[x][y]);
        }
        printf("\n");
    }
}

bool isLegal(int x, int y, Grid *grid)
{
    if (!(x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT))
    {
        return false;
    }
    if (*grid[x][y] == 'X') 
    {
        return false;
    }
    return true;
}

bool drawCharToGrid(char c, int x, int y, Grid* grid)
{
    if (isLegal(x, y, grid))
    {
        *grid[x][y] = c;
        return true;
    }
    return false;
}
