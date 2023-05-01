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

coord* create_coord();
void destroy_coord(coord* point);
double get_coord_x(coord* point);
void set_coord_x(coord* point, double x);
double get_coord_y(coord* point);
void set_coord_y(coord* point, double y);
void set_coord(coord* point, double x, double y);

double distance(coord* p1, coord* p2);
float distance_euclid(coord* p1, coord* p2);
bool excl_carre(coord* point, coord* dep, coord* arr, int marge);
bool excl_ovale(coord* point, coord* dep, coord* arr, double marge);

#endif
