#ifndef _MATRICE_H_
#define _MATRICE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct matrice_inf
{
    int taille;
    float** mat;
} matrice_inf;

//float** create_matrice(int n); // Seulement dans le module matrice.c
//void destroy_matrice(float** mat, int n); // Seulement dans le module matrice.c

matrice_inf* create_matrice_struc(int n);
float get_element_matrice_struc(matrice_inf* mat_s, int i, int j);
void set_element_matrice_struc(matrice_inf* mat_s, int i, int j, float val);
void destroy_matrice_struc(matrice_inf* mat_s);
int size_matrice_struc(matrice_inf* mat_s);

void print_matrice_struc(matrice_inf* mat_s);

#endif
