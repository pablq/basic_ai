#include <stdlib.h>
#include "location.h"

Location *newLocation(int x, int y)
{
    Location *l = malloc(sizeof(Location));
    l->x = x;
    l->y = y;
    return l;
}

void deleteLocation(Location *l)
{
    free(l);
}
