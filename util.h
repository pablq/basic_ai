#ifndef UTIL
#define UTIL

#include <stdbool.h>

int randInRange(int low, int high); // INCLUSIVE

bool sameLocation(int x1, int y1, int x2, int y2);

int manhattanDistance(int x1, int y1, int x2, int y2);

int max(int n1, int n2);

#endif /* UTIL */
