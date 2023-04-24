#ifndef __POTAGIBUS_H__
#define __POTAGIBUS_H__
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "station.h"
#include "voiture.h"
 

list_t* Selection_de_points(coord* depart, coord* arrivee, list_t* liste_point);

list_t* Selection_de_points_int(coord* depart, coord* arrivee, list_t* liste_point, int marge);

float** Gen_Matrice(list_t* List_points_Trie, int taille);

matrice_inf* Gen_Matrice_struc(list_t* List_points_Trie);

#endif
