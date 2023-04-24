#ifndef _MATRICE_H_
#define _MATRICE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct matrice_inf
{
    int taille;
    float** mat;
} typedef matrice_inf;

float** create_matrice(int n);
void destroy_matrice(float** mat, int n);

matrice_inf* create_matrice_struc(int n);
float get_element_matrice_struc(matrice_inf* mat_s, int i, int j);
void set_element_matrice_struc(matrice_inf* mat_s, int i, int j, float val);
void destroy_matrice_struc(matrice_inf* mat_s);
int size_matrice_struc(matrice_inf* mat_s);

#endif
