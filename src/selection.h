#ifndef _SELECTION_H_
#define _SELECTION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "station.h"
#include "coord.h"
#include "list_int.h"
#include "matrice.h"

// list_int* select_point_list(coord* depart, coord* arrivee, station_tab* tab_s, int marge); N'est utilisé que dans le module selection.c
corresp_station_tab* select_point_struct(coord* depart, coord* arrivee, station_tab* tab_s, double marge);
// matrice_inf* generate_adj_matrice_corresp(corresp_station_tab* corresp, coord* depart, coord* arrivee, station_tab* tab_s); N'est plus utilisé
matrice_inf* generate_adj_matrice(station_tab* tab_s);

#endif
