#ifndef LOCATION
#define LOCATION

typedef struct Location
{
    int x;
    int y;
} Location;

Location *newLocation(int x, int y);

void deleteLocation(Location *location);
#endif /* LOCATION */
