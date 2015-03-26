#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "grid.h"

void printGridAsChars(Grid grid);

void printGrid(Grid grid);

bool isLegal(int x, int y, Grid grid);

Grid copyGrid(Grid original);

void buildLayout(Grid grid);

Grid newGrid(void)
{
    Grid myGrid = malloc(sizeof(int *) * GRID_WIDTH);
    for (int i = 0; i < GRID_WIDTH; i += 1)
    {
        myGrid[i] = malloc(sizeof(int) * GRID_HEIGHT);
    }
    return myGrid;
}

void deleteGrid(Grid grid)
{
    for (int i = 0; i < GRID_WIDTH; i += 1)
    {
        free(grid[i])
    }
    free(grid);
}

void buildLayout(Grid grid)
{
    // this is the basic build. it just populates the outside with walls
    // all locations in the grid have a value. walls are 0 and available space range
    // in value from 1 to 9.
    // 1 is the base value and, for now, every spot will have a value of 1
    for (int x = 0; x < GRID_WIDTH; x += 1) 
    {
        for (int y = 0; y < GRID_HEIGHT; y += 1) 
        {
            if ((y == 0 || y == GRID_HEIGHT - 1) || (x == 0 || x == GRID_WIDTH - 1))
            {
                grid[x][y] = 0;
            } else {
                grid[x][y] = 1;
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
            grid[x][y] = 0;
            if (is_horiz) { // for horizontal walls
                // if the next block is already a wall or there is a wall above or below, we're done with this wall
                if ((j > 0 && j < len - 1) && (grid[x+1][y] == 0 || grid[x][y+1] == 0 || grid[x][y-1] == 0))
                {
                    break;
                } else { // otherwise, advance to the next block
                    x += 1;
                }
            } else { // for vertical walls
                // if the next block is already a wall or there is a wall to the right or left, we're done with this wall
                if ((j > 0 && j < len - 1) && (grid[x+1][y] == 0 || grid[x][x-1] == 0))
                {
                    break;
                } else { // otherwise, advance to the next block
                    y += 1;
                }
            }
        }
    }
}

Grid copyGrid(Grid original)
{
    Grid copy = newGrid();

    for (int y = 0; y < GRID_HEIGHT; y += 1) 
    {
        for (int x = 0; x < GRID_WIDTH; x += 1) 
        {
            copy[x][y] = original[x][y];
        }
    }
    return copy;
}

bool sameGrid(Grid model, Grid check)
{
    for (int y = 0; y < GRID_HEIGHT; y += 1) 
    {
        for (int x = 0; x < GRID_WIDTH; x += 1) 
        {
            if (model[x][y] != check[x][y]) 
            {
                return false;
            }
        }
    }
    return true;
}

void printGrid(Grid grid)
{
    for (int y = 0; y < GRID_HEIGHT; y += 1) 
    {
        for (int x = 0; x < GRID_WIDTH; x += 1) 
        {
            printf("%d", grid[x][y]);
        }
        printf("\n");
    }
}

void printGridAsChars(Grid grid)
{
    for (int y = 0; y < GRID_HEIGHT; y += 1) 
    {
        for (int x = 0; x < GRID_WIDTH; x += 1) 
        {
            printf("%c", grid[x][y]);
        }
        printf("\n");
    }
}

bool isLegal(int x, int y, Grid grid)
{
    if (!(x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT))
    {
        return false;
    }
    if (grid[x][y] == 0) 
    {
        return false;
    }
    return true;
}
