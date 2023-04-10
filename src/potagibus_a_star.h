#ifndef __POTAGIBUS_A_STAR_H__
#define __POTAGIBUS_A_STAR_H__
#include <stdbool.h>
#include <stdio.h>

#define INITIAL_SIZE 50


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

struct garbage_list
{
    chemin** chemin;
    int taille;
    int taille_max;
} typedef garbage_list;

#endif