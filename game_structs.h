#ifndef GAME_STRUCTS
#define GAME_STRUCTS

typedef struct LocationStruct
{
    int x;
    int y;
} Location;

typedef struct AgentStruct
{
    Location loc;
    char face;
    char moves[];
} Agent;

typedef char Grid[50][50];

#endif
