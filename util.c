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
