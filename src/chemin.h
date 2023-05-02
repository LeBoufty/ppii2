#ifndef _CHEMIN_H_
#define _CHEMIN_H_

#include <stdio.h>
#include <stdlib.h>
#include "station.h"
#include "voiture.h"

struct chemin_tab
{ 
    int id; // Identifiant de la station, -1 si départ, -2 si arrivée
    double distance_prochain; // Distance à la prochaine station, -1 s'il n'y en a pas (arrivée)
    double capacite_avant; // Capacité de la voiture au début de la station (avant recharge), en Wh
    double capacite_apres; // Capacité de la voiture à la fin de la station (après recharge), en Wh
} typedef chemin_tab;

struct chemin_tab_struct
{
    chemin_tab* tab;
    int taille;
    station_tab* s_tab; // Lien vers le tableau de stations
    int id_v;
    voiture_tab* v_tab; // Lien vers le tableau de voitures
} typedef chemin_tab_struct;

chemin_tab_struct* create_chemin_tab_struct(int taille, station_tab* tab_s, voiture_tab* tab_v, int id_v);
void destroy_chemin_tab_struct(chemin_tab_struct* cts);
int size_chemin_tab_struct(chemin_tab_struct* cts);
double get_chemin_tab_struct_temps_recharge(chemin_tab_struct* cts, int i);
double get_chemin_tab_struct_temps_prochain(chemin_tab_struct* cts, int i, int vitesse);

void set_chemin_tab_struct_id_station(chemin_tab_struct* cts, int i, int id);
int get_chemin_tab_struct_id_station(chemin_tab_struct* cts, int i);
int get_chemin_tab_struct_id_voiture(chemin_tab_struct* cts);
void set_chemin_tab_struct_distance_prochain(chemin_tab_struct* cts, int i, double distance_prochain);
double get_chemin_tab_struct_distance_prochain(chemin_tab_struct* cts, int i);
void set_chemin_tab_struct_capacite_avant(chemin_tab_struct* cts, int i, double capacite_avant);
double get_chemin_tab_struct_capacite_avant(chemin_tab_struct* cts, int i);
void set_chemin_tab_struct_capacite_apres(chemin_tab_struct* cts, int i, double capacite_apres);
double get_chemin_tab_struct_capacite_apres(chemin_tab_struct* cts, int i);

#endif
