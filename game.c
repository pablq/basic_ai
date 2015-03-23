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

#ifndef STDBOOL
#define STDBOOL
#include <stdbool.h>
#endif

#ifndef PROBLEM
#define PROBLEM
#include "problem.h"
#endif

#ifndef GAME
#define GAME
#include "game.h"
#endif

void placeGoal(Location *goal, Grid *grid);

void placeStart(Location *start, Grid *grid);

bool isLegal(int x, int y, Grid *grid);

bool isWin(Game *game);

bool sameLocation(Location *a, Location *b);

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
            return false;
    }
    
    if (!isLegal(new_x, new_y, game->grid)) 
    {
        return false;
    }

    game->agent->x = new_x;
    game->agent->y = new_y;

    return true;
}

bool isLegal(int x, int y, Grid *grid)
{
    if (x > WIDTH - 1 || x < 0 || y > HEIGHT - 1 || y < 0) 
    {
        return false;
    }
    if (*grid[x][y] == 'X') 
    {
        return false;
    }
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
            printf("ILLEGAL ACTION ATTEMPTED. ABORTING GAME\n");
            break;
        }
    }

    if (winner)
    {
        printf("WINNER!\n");
    } else {
        printf("GAME OVER.\n");
    }
}
        
void placeStart(Location *start, Grid *grid)
{
    bool placed = false;
    while (!placed)
    {
        int x = randInRange(0,WIDTH - 1);
        int y = randInRange(0,HEIGHT - 1);

        if (*grid[x][y] != 'X' && *grid[x][y] != 'G')
        {
            *grid[x][y] = 'A';

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
