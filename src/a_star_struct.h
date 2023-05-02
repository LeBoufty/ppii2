#ifndef _A_STAR_STRUCT_H_
#define _A_STAR_STRUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#define INITIAL_SIZE_GARBAGE 50 // Taille initiale de la liste de garbage

struct garbage_chemin
{
    chemin** chemin;
    int taille;
    int taille_max;
} typedef garbage_chemin;

struct chemin
{
    struct chemin* suivant;
    int id; // Identifiant de la station, -1 si départ, -2 si arrivée
    double distance_total; // Distance parcourue depuis le départ, en km, utile pour la file du A*
    double distance_prochain; // Distance à la prochaine station, -1 s'il n'y en a pas (arrivée)
    double capacite_avant; // Capacité de la voiture au début de la station (avant recharge), en Wh
    double capacite_apres; // Capacité de la voiture à la fin de la station (après recharge), en Wh
} typedef chemin;


struct file
{
    struct file* suivant;
    struct file* precedent;
    chemin* chemin;
    float distance_approche;
    int id;
  
} typedef file;



chemin* create_chemin();
chemin* push_chemin(chemin* c, int id, float distance);
int size_chemin(chemin* c);
float distance_chemin(chemin* c);
int* copy_chemin(chemin* c);
void destroy_chemin(chemin* c);

garbage_chemin* create_garbage_chemin();
void push_garbage_chemin(garbage_chemin* g, chemin* c);
void destroy_garbage_chemin(garbage_chemin* g);

file* create_file();
void enqueue_file(file* f, chemin* c, int id, float distance_approche);
void dequeue(file* f, chemin** c, int* id, float* distance_approche);
bool is_empty_file(file* f);
bool is_next_file(file* f, int id);
void destroy_file(file* f);



#endif
