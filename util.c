#include <stdlib.h>
#include <time.h>

int randInRange(int low, int high)
{
    int offset, r;

    offset = rand();
    srand(time(NULL) + offset);

    r = rand();
    return low + (r % (high + 1 - low));
}

int pointerHash(void *pointer)
{
   return (int) (unsigned long) pointer; 
} 

int hashLocation(int x, int y)
{
    return x + y;
}
