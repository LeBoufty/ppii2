#ifndef stationtxt_h
#define stationtxt_h
#include "traitementP2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction qui permet de créer le fichier station.txt à l'instant N
void createStationFile(int N, station_tab* list_s);

// Fonction qui permet de créer le fichier coordonnees.txt
void createCoordFile(station_tab* list_s);


#endif
