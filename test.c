#include <stdio.h>
#include "util.h"

int main (void) {
    
    for (int i = 0; i < 25; i += 1)
    {
        printf("%d\n", randInRange(0,10));
    }
} 
