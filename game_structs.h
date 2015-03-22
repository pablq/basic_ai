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

#endif
