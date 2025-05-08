#ifndef _STATION_H_
#define _STATION_H_

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "coord.h"

#define LENGTH_ID 40

// Structure de données pour les stations
typedef struct station {
    char id[LENGTH_ID];
    coord* coord;
    int nbre_pdc;
    int nbre_pdc_dispo;
    int puissance;
} station;

// Structure de données de tableau de stations
typedef struct station_tab
{
    int taille;
    station* tab;
} station_tab;


// Structure de données pour les correspondances entre le tableau de stations et le tableau de stations trié
typedef struct corresp_station_tab
{
    int taille;
    int* tab_id;
} corresp_station_tab;

station_tab* create_station_tab(int taille);
void destroy_station_tab(station_tab* tab_s);
void print_station_tab(station_tab* tab_s, int i);
int size_station_tab(station_tab* tab_s);

station* get_station_tab(station_tab* tab_s, int i);
void set_station_tab(station_tab* tab_s, int i, station* s);
char* get_station_tab_id(station_tab* tab_s, int i);
void set_station_tab_id(station_tab* tab_s, int i, char* id);
coord* get_station_tab_coord(station_tab* tab_s, int i);
double get_station_tab_coord_x(station_tab* tab_s, int i);
double get_station_tab_coord_y(station_tab* tab_s, int i);
void set_station_tab_coord_x(station_tab* tab_s, int i, double x);
void set_station_tab_coord_y(station_tab* tab_s, int i, double y);
int get_station_tab_nbre_pdc(station_tab* tab_s, int i);
void set_station_tab_nbre_pdc(station_tab* tab_s, int i, int nbre_pdc);
int get_station_tab_nbre_pdc_dispo(station_tab* tab_s, int i);
void set_station_tab_nbre_pdc_dispo(station_tab* tab_s, int i, int nbre_pdc_dispo);
void add_station_tab_nbre_pdc_dispo(station_tab* tab_s, int i, int valeur_nbre_pdc_dispo);
int get_station_tab_puissance(station_tab* tab_s, int i);
void set_station_tab_puissance(station_tab* tab_s, int i, int puissance);

corresp_station_tab* create_corresp_tab(int taille);
void destroy_corresp_tab(corresp_station_tab* tab_c);
int size_corresp_tab(corresp_station_tab* tab_c);

int get_corresp_tab_id(corresp_station_tab* tab_c, int i);
void set_corresp_tab_id(corresp_station_tab* tab_c, int i, int id);

#endif
