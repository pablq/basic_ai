#ifndef STDIO
#define STDIO
#include <stdio.h>
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef GRID
#define GRID
#include "grid.h"
#endif

#ifndef GRID_DIMS
#define GRID_DIMS
#define GRID_WIDTH 50
#define GRID_HEIGHT 25
#endif

#ifndef LOCATION
#define LOCATION
#include "location.h"
#endif

#ifndef STDBOOL
#define STDBOOL
#include <stdbool.h>
#endif

#ifndef UTIL
#define UTIL
#include "util.h"
#endif

#ifndef GAME
#define GAME
#include "game.h"
#endif

void placeGoal(Location *goal, Grid *grid);

void placeStart(Location *start, Grid *grid);

bool isWin(Game *game);

bool sameLocation(Location *a, Location *b);

void drawMove(char move, Location *agent, Grid *grid);

void drawWinner(Location *winner, Grid *grid);

Game *newGame(void)
{

    Grid *grid = malloc(sizeof(Grid));
    buildLayout(grid);

    Location *start = malloc(sizeof(Location));
    placeStart(start, grid);

    Location *goal = malloc(sizeof(Location));
    placeGoal(goal, grid);

    Location *agent = malloc(sizeof(Location));
    *agent = *start;

    Game *game = malloc(sizeof(Game));
    game->grid = grid;
    game->start = start;
    game->agent = agent;
    game->goal = goal;
    game->isWin = false;

    return game;
}

void deleteGame(Game *game)
{
    free(game->grid);
    free(game->start);
    free(game->goal);
    free(game->agent);
    free(game);
}

bool moveAgent(char action, Game *game)
{
    int new_x, new_y;
    int x = game->agent->x;
    int y = game->agent->y;

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
        case 'E':
            new_x = x + 1;
            new_y = y;
            break;
        case 'W':
            new_x = x - 1;
            new_y = y;
            break;
        default:
            printf("UNRECOGNIZED ACTION: %c\n", action);
            return false;
    }

    if (!isLegal(new_x, new_y, game->grid)) 
    {
        printf("ILLEGAL MOVE: (%d,%d)->(%d,%d) with action %c\n",x,y,new_x,new_y,action);
        return false;
    }

    game->agent->x = new_x;
    game->agent->y = new_y;

    printf("SUCCESSFUL MOVE: (%d,%d)->(%d,%d) with action %c\n",x,y,new_x,new_y,action);
    return true;
}

bool isWin(Game *game)
{
    return sameLocation(game->agent, game->goal);
}

bool sameLocation(Location *a, Location *b)
{
    return (a->x == b->x && a->y == b->y);
}

void play(char *actions, Game *game)
{
    bool winner = false;
    int i = 0;
    while(actions[i] != '\0')
    {
        if (isWin(game)) 
        {
            winner = true;
            break;
        }

        char action = actions[i];

        if (!moveAgent(action, game))
        {
            break;
        }

        drawMove(action, game->agent, game->grid);

        i += 1;
    }

    if (winner)
    {
        drawWinner(game->agent, game->grid);
        printf("WINNER!\n");
    } else {
        printf("GAME OVER.\n");
    }
}

// the below functions all use the grid api's drawCharToGrid function to actually draw on the grid

void drawMove(char move, Location *agent, Grid *grid)
{
    int x = agent->x;
    int y = agent->y;
    char mark = '?';
    switch (move)
    {
        case 'N':
            mark = '^';
            break;
        case 'S':
            mark = 'v';
            break;
        case 'E':
            mark = '>';
            break;
        case 'W':
            mark = '<';
            break;
    }

    if (isLegal(x,y,grid))
    {
        drawCharToGrid(mark,x,y,grid);
    }
}

void drawWinner(Location *winner, Grid *grid)
{
    int x = winner->x;
    int y = winner->y;
    if (isLegal(x,y,grid))
    {
        drawCharToGrid('W',x,y,grid);
    }
}

// these two are special because they draw to the grid AND populate Location structs
        
void placeStart(Location *start, Grid *grid)
{
    bool placed = false;
    while (!placed)
    {
        int x = randInRange(0,GRID_WIDTH - 1);
        int y = randInRange(0,GRID_HEIGHT - 1);

        if (isLegal(x,y,grid) && *grid[x][y] != 'G')
        {
            drawCharToGrid('S',x,y,grid);
            start->x = x;
            start->y = y;
            placed = true;
        }
    }
}

void placeGoal(Location *goal, Grid *grid)
{
    bool placed = false;
    while (!placed)
    {
        int x = randInRange(0,GRID_WIDTH - 1);
        int y = randInRange(0,GRID_HEIGHT - 1);

        if (isLegal(x,y, grid) && *grid[x][y] != 'S')
        {
            drawCharToGrid('G',x,y,grid);
            goal->x = x;
            goal->y = y;
            placed = true;
        }
    }
}
