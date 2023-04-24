#ifndef _STATION_H_
#define _STATION_H_

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LENGTH_ID 40

// Structure de données pour les stations
struct station {
    char id[LENGTH_ID];
    double longitude;
    double latitude;
    int nbre_pdc;
    int nbre_pdc_dispo;
    int puissance;
} typedef station;

// Structure de données de tableau de stations
struct station_tab
{
    int taille;
    station* tab;
} typedef station_tab;


// Structure de données pour les correspondances entre le tableau de stations et le tableau de stations trié
struct corresp_station
{
    int id;
    int id_station_tab;
} typedef corresp_station;

struct corresp_station_tab
{
    int taille;
    corresp_station* tab;
} typedef corresp_station_tab;

station_tab* create_station_tab(int taille);
void destroy_station_tab(station_tab* tab_s);
void print_station_tab(station_tab* tab_s, int i);
int size_station_tab(station_tab* tab_s);

station* get_station_tab(station_tab* tab_s, int i);
void set_station_tab(station_tab* tab_s, int i, station* s);
char* get_station_tab_id(station_tab* tab_s, int i);
void set_station_tab_id(station_tab* tab_s, int i, char* id);
double get_station_tab_longitude(station_tab* tab_s, int i);
void set_station_tab_longitude(station_tab* tab_s, int i, double longitude);
double get_station_tab_latitude(station_tab* tab_s, int i);
void set_station_tab_latitude(station_tab* tab_s, int i, double latitude);
int get_station_tab_nbre_pdc(station_tab* tab_s, int i);
void set_station_tab_nbre_pdc(station_tab* tab_s, int i, int nbre_pdc);
int get_station_tab_nbre_pdc_dispo(station_tab* tab_s, int i);
void set_station_tab_nbre_pdc_dispo(station_tab* tab_s, int i, int nbre_pdc_dispo);
int get_station_tab_puissance(station_tab* tab_s, int i);
void set_station_tab_puissance(station_tab* tab_s, int i, int puissance);

#endif