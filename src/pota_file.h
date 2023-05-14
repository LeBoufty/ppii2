#ifndef _POTA_FILE_H_
#define _POTA_FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "station.h"
#include "voiture.h"

#define BUFFER_SIZE 200

// int nb_ligne(const char *filename); // Seulement pour pota_file.c
station_tab* read_csv_station_tab(const char* filename);
voiture_tab* read_csv_voiture_tab(const char* filename);

#endif
