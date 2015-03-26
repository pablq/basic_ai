#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int randInRange(int low, int high)
{
    int offset, r;

    offset = rand();
    srand(time(NULL) + offset);

    r = rand();
    return low + (r % (high + 1 - low));
}

unsigned int pointerHash(void *pointer)
{
   return (unsigned int) (unsigned long) pointer; 
} 

bool sameLocation(int x1, int y1, int x2, int y2)
{
    return  (x1 == x2 && y1 == y2);
}
