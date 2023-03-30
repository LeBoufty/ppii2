#ifndef __POTAGIBUS_H__
#define __POTAGIBUS_H__
#include<stdbool.h>

struct _coord
{
    int x;
    int y;
};

typedef struct _coord coord;
bool excl_carre(coord* point, coord* dep, coord* arr, int marge);

bool excl_ovale(coord* point, coord* dep, coord* arr);
#endif