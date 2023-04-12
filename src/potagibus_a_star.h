#ifndef __POTAGIBUS_A_STAR_H__
#define __POTAGIBUS_A_STAR_H__
#include <stdbool.h>
#include <stdio.h>
#include "potagibus_fct.h"

#define INITIAL_SIZE 50 // Taille initiale de la liste de garbage
#define LAMBDA 1.5 // Coefficient de pondération de la distance approchée


struct chemin
{
    struct chemin* suivant;
    int id;
    float distance;
} typedef chemin;


struct file
{
    struct file* suivant;
    struct file* precedent;
    chemin* chemin;
    float distance_approche;
    int id;
  
} typedef file;

struct garbage_chemin
{
    chemin** chemin;
    int taille;
    int taille_max;
} typedef garbage_chemin;

chemin* create_chemin();
chemin* push_chemin(chemin* c, int id, float distance);
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

int* a_star(matrice_inf* mat_st, int depart, int arrivee, float distance_max);

#endif
