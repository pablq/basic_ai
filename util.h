#ifndef UTIL
#define UTIL

#include <stdbool.h>

int randInRange(int low, int high);

unsigned int pointerHash(void *pointer);

bool sameLocation(int x1, int y1, int x2, int y2);

#endif /* UTIL */
