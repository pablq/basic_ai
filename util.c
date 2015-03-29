#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int randInRange(int low, int high) // *INCLUSIVE
{
    int offset, r;

    offset = rand();
    srand(time(NULL) + offset);

    r = rand();

    return low + (r % (high + 1 - low));
}

bool sameLocation(int x1, int y1, int x2, int y2)
{
    return  (x1 == x2 && y1 == y2);
}

int manhattanDistance(int x1, int y1, int x2, int y2)
{
    return abs((x1 - x2) + (y1 - y2));
}

int max(int n1, int n2)
{
    return (n1 > n2) ? n1 : n2;
}
