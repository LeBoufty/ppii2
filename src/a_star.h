#ifndef __A_STAR_H__
#define __A_STAR_H__
#include <stdbool.h>
#include <stdio.h>
#include "chemin.h"
#include "a_star_struct.h"
#include "selection.h"
#include "matrice.h"

#define LAMBDA 1.5 // Coefficient de pondération de la distance approchée
#define MARGE 20 // Marge de sécurité pour les stations sélectionnées

// double min(double a, double b); // Seulement dans le module a_star.c
// chemin_tab_struct* chemin_to_chemin_tab_struct(chemin* chemin, corresp_station_tab* corresp, station_tab* tab_s, voiture_tab* tab_v, int id_voiture); // Seulement dans le module a_star.c
chemin_tab_struct* a_star(matrice_inf* mat_st, coord* depart, coord* arrivee, station_tab* tab_s, voiture_tab* tab_v, int id_voiture, double temps_recharge_max, double minimum_percent_battery, double capacite_depart);


#endif
