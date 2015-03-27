#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"
#include "location.h"
#include "util.h"
#include "game.h"

bool moveAgent(char action, Game *game);

bool isWin(Game *game);

void drawMove(char move, Game *game);

void drawWinner(Game *game);

void placeStart(Location *start, Game *game);

void placeGoal(Location *goal, Game *game);

Grid newDisplay(Grid board);

Grid newBoard(void);

Game *newGame(void)
{
    Game *game = malloc(sizeof(Game));

    Grid board = newBoard();
    game->board = board;

    Grid display = newDisplay(board);
    game->display = display;

    Location *start = newLocation(0,0); // placeStart gives it real values
    placeStart(start, game);
    game->start = start;

    Location *goal = newLocation(0,0);
    placeGoal(goal, game);

    Location *agent = newLocation(start->x,start->y);
    game->agent = agent;
    
    printGridAsChars(game->display);

    return game;
}

Grid newBoard(void)
{
    Grid board = newGrid();
    return board;
}

void playGame(char *actions, Game *game)
{
    bool winner = false;
    int i = 0;
    while(actions != NULL && actions[i] != '\0')
    {
        char action = actions[i];

        if (!moveAgent(action, game))
        {
            break;
        }

        if (isWin(game)) 
        {
            winner = true;
            break;
        }

        i += 1;
    }

    if (winner)
    {
        drawWinner(game);
        printf("WINNER!\n");
    } else {
        printf("YOU DID NOT REACH GOAL.\n");
    }

    printGridAsChars(game->display);
}

void deleteGame(Game *game)
{
    deleteGrid(game->board);
    deleteGrid(game->display);
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
        case 'n':
            new_x = x;
            new_y = y - 1;
            break;
        case 's':
            new_x = x;
            new_y = y + 1;
            break;
        case 'e':
            new_x = x + 1;
            new_y = y;
            break;
        case 'w':
            new_x = x - 1;
            new_y = y;
            break;
        default:
            printf("UNRECOGNIZED ACTION: %c\n", action);
            return false;
    }

    if (!isLegal(new_x, new_y, game->board)) 
    {
        printf("ILLEGAL MOVE: (%d,%d)->(%d,%d) with action '%c'.\n",x,y,new_x,new_y,action);
        return false;
    }

    game->agent->x = new_x;
    game->agent->y = new_y;

    // this is a side effect -> it draw's the actual move to the game's display grid.
    drawMove(action, game);

    return true;
}

bool isWin(Game *game)
{
    return sameLocation(game->agent->x, game->agent->y, game->goal->x, game->goal->y);
}

// the below functions all use the drawCharToGrid function to actually draw on the grid

bool writeCharToGrid(char c, int x, int y, Grid grid)
{
    if (isLegal(x, y, grid))
    {
        grid[x][y] = c;
        return true;
    }
    return false;
}

Grid newDisplay(Grid board)
{
    Grid display = copyGrid(board);

    for (int y = 0; y < GRID_HEIGHT; y += 1) 
    {
        for (int x = 0; x < GRID_WIDTH; x += 1) 
        {
            char c;
            switch (board[x][y])
            {
                case 0:
                    c = 'X';
                    break;
                case 1:
                    c = '.';
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                    c = display[x][y] + 48;
                    break;
                default:
                    c = display[x][y];
            }
            display[x][y] = c;
        }
    }

    return display;
}

void drawWinner(Game *game)
{
    writeCharToGrid('W', game->goal->x, game->goal->y, game->display);
}

void drawMove(char move, Game *game)
{
    int x = game->agent->x;
    int y = game->agent->y;
    char mark = 'Z';
    switch (move)
    {
        case 'n':
            mark = '^';
            break;
        case 's':
            mark = 'v';
            break;
        case 'e':
            mark = '>';
            break;
        case 'w':
            mark = '<';
            break;
        default:
            mark = 'x';
            break;
    }

    if (isLegal(x,y,game->board))
    {
        writeCharToGrid(mark,x,y,game->display);
    }
}

// these two are special because they draw to the grid AND populate Location structs
        
void placeStart(Location *start, Game *game)
{
    bool placed = false;
    while (!placed)
    {
        int x = randInRange(0,GRID_WIDTH - 1);
        int y = randInRange(0,GRID_HEIGHT - 1);

        if (isLegal(x,y,game->board) && game->display[x][y] != 'G')
        {
            writeCharToGrid('S',x,y,game->display);
            start->x = x;
            start->y = y;
            placed = true;
        }
    }
    game->start = start;
}

void placeGoal(Location *goal, Game *game)
{
    bool placed = false;
    while (!placed)
    {
        int x = randInRange(0,GRID_WIDTH - 1);
        int y = randInRange(0,GRID_HEIGHT - 1);

        if (isLegal(x,y, game->board) && game->display[x][y] != 'S')
        {
            writeCharToGrid('G',x,y,game->display);
            goal->x = x;
            goal->y = y;
            placed = true;
        }
    }
    game->goal = goal;
}
