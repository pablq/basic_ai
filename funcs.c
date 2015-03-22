#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

#ifndef TIME
#define TIME
#include <time.h>
#endif


int randInRange(int low, int high)
{
    int offset, r;

    offset = rand();
    srand(time(NULL) + offset);

    r = rand();
    return low + (r % (high + 1 - low));
}
