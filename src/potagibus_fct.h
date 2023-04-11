#ifndef __POTAGIBUS_H__
#define __POTAGIBUS_H__
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

struct Station {
    char id[32];
    float longitude;
    float latitude;
    int nbre_pdc;
    struct Station* next;
};

struct _coord
{
    float x;
    float y;
};

typedef struct _coord coord;

struct _list_t { coord* element;struct _list_t* next;};

typedef struct _list_t list_t;

struct Station* read_csv(const char* filename);

float** create_Matrice(int n);

float element_mat(float** mat,int x, int y);

float distance(coord* p1, coord* p2);

list_t* Selection_de_points(coord* depart, coord* arrivee, list_t* liste_point);

list_t* Selection_de_points_int(coord* depart, coord* arrivee, list_t* liste_point, int marge);

float** Gen_Matrice(list_t* List_points_Trie, int taille);

list_t *list_create();

void list_destroy(list_t *one_list);

bool list_is_empty(list_t *one_list);

void list_append(list_t* one_list, float coord_x, float coord_y);

void element_print(coord *one_element);

void list_print(list_t *one_list);

int list_size(list_t* one_list);

bool excl_carre(coord* point, coord* dep, coord* arr, int marge); 

bool excl_ovale(coord* point, coord* dep, coord* arr, int marge);

int taille_matrice(float** mat_adj);

#endif
