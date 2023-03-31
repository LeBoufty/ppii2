#ifndef __POTAGIBUS_H__
#define __POTAGIBUS_H__
#include<stdbool.h>

struct _coord
{
    float x;
    float y;
};

typedef struct _coord coord;

bool excl_carre(coord* point, coord* dep, coord* arr, int marge); 

bool excl_ovale(coord* point, coord* dep, coord* arr, int marge);

float** create_Matrice(int n);

float distance(coord* p1, coord* p2);

#endif
