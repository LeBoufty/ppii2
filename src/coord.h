#ifndef _COORD_H_
#define _COORD_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEG_TO_RAD 0.0174532925

struct coord
{
    double x;
    double y;
} typedef coord;

float distance(coord* p1, coord* p2);
float distance_euclid(coord* p1, coord* p2);
bool excl_carre(coord* point, coord* dep, coord* arr, int marge);
bool excl_ovale(coord* point, coord* dep, coord* arr, int marge);

#endif
