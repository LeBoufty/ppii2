#ifndef __POTAGIBUS_H__
#define __POTAGIBUS_H__
#include<stdbool.h>

struct _coord
{
    float x;
    float y;
};

typedef struct _coord coord;

struct _list_t { coord* element;struct _list_t* next;};

typedef struct _list_t list_t;

list_t *list_create();

void list_destroy(list_t *one_list);

bool list_is_empty(list_t *one_list);

void list_append(list_t* one_list, float coord_x, float coord_y);

void element_print(coord *one_element);

void list_print(list_t *one_list);

bool excl_carre(coord* point, coord* dep, coord* arr, int marge); 

bool excl_ovale(coord* point, coord* dep, coord* arr, int marge);

float** create_Matrice(int n);

float distance(coord* p1, coord* p2);

float** suppr_point(coord* depart, coord* arrivée, float** tableau);

#endif
