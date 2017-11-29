//
//  header.h

#ifndef header_h
#define header_h

#define N 4

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
struct rectangle {
    int x1, y1;
    int x2, y2;
    int x3, y3;
    int x4, y4;
};
int test(struct rectangle rect);
float perim(struct rectangle rect);
float square(struct rectangle rect);

#endif
