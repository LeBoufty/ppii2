#ifndef _POTA_FILE_H_
#define _POTA_FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "station.h"
#include "voiture.h"
#include "chemin.h"
#include "coord.h"

#define BUFFER_SIZE 200

// int nb_ligne(const char *filename); // Seulement pour pota_file.c
station_tab* read_csv_station_tab(const char* filename);
voiture_tab* read_csv_voiture_tab(const char* filename);
void write_txt_chemin_tab_struct(chemin_tab_struct* chemin, station_tab* tab_s, coord* depart, coord* arrivee);

#endif
