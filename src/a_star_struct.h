#ifndef _A_STAR_STRUCT_H_
#define _A_STAR_STRUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define INITIAL_SIZE_GARBAGE 50 // Taille initiale de la liste de garbage

struct chemin
{
    struct chemin* suivant;
    int id; // Identifiant de la station, -1 si départ, -2 si arrivée
    double distance_total; // Distance parcourue depuis le départ, en km, utile pour la file du A*
    double distance_prochain; // Distance à la prochaine station, -1 s'il n'y en a pas (arrivée)
    double capacite_avant; // Capacité de la voiture au début de la station (avant recharge), en Wh
    double capacite_apres; // Capacité de la voiture à la fin de la station (après recharge), en Wh
} typedef chemin;

struct garbage_chemin
{
    chemin** chemin;
    int taille;
    int taille_max;
} typedef garbage_chemin;

struct file
{
    struct file* suivant;
    struct file* precedent;
    chemin* chemin;
    double distance_approche;
  
} typedef file;

struct visite_tab
{
    int* tab;
    int taille;
} typedef visite_tab;


chemin* create_chemin(garbage_chemin* gc);
chemin* push_chemin(chemin* c, int id, double distance, double capacite_avant, double capacite_apres, garbage_chemin* gc);
int size_chemin(chemin* c);
int get_chemin_id(chemin* c);
double get_chemin_distance_totale(chemin* c);
double get_chemin_distance_prochain(chemin* c);
double get_chemin_capacite_avant(chemin* c);
double get_chemin_capacite_apres(chemin* c);

int* copy_chemin(chemin* c);
void destroy_chemin(chemin* c);

garbage_chemin* create_garbage_chemin();
void push_garbage_chemin(garbage_chemin* g, chemin* c);
void destroy_garbage_chemin(garbage_chemin* g);

file* create_file();
void enqueue_file(file* f, chemin* c, double distance_approche);
chemin* dequeue_file(file* f);
bool is_empty_file(file* f);
bool is_next_file(file* f, int id);
void destroy_file(file* f);

visite_tab* create_visite_tab(int taille);
bool get_visite_tab(visite_tab* v, int i);
void set_visite_tab(visite_tab* v, int i, bool value);
void destroy_visite_tab(visite_tab* v);

#endif
