#ifndef __POTAGIBUS_A_STAR_H__
#define __POTAGIBUS_A_STAR_H__
#include <stdbool.h>
#include <stdio.h>
#include "chemin.h"
#include "a_star_struct.h"

#define LAMBDA 1.5 // Coefficient de pondération de la distance approchée




int* a_star(matrice_inf* mat_st, int depart, int arrivee, float distance_max);

#endif
