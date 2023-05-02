#ifndef _VOITURE_H_
#define _VOITURE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define LENGTH_NAME 40


struct voiture {
    char name[LENGTH_NAME];
    int range; // en km
    int efficiency; // en Wh/km
    int fast_charge; // en km/h
} typedef voiture;

struct voiture_tab
{
    int taille;
    voiture* tab;
} typedef voiture_tab;


voiture_tab* create_voiture_tab(int taille);
void destroy_voiture_tab(voiture_tab* v);
void print_voiture_tab(voiture_tab* v, int i);
int size_voiture_tab(voiture_tab* v);

voiture* get_voiture_tab(voiture_tab* v, int i);
void set_voiture_tab(voiture_tab* v, int i, voiture* s);

char* get_voiture_tab_name(voiture_tab* v, int i);
void set_voiture_tab_name(voiture_tab* v, int i, char* name);
int get_voiture_tab_range(voiture_tab* v, int i);
void set_voiture_tab_range(voiture_tab* v, int i, int range);
int get_voiture_tab_efficiency(voiture_tab* v, int i);
void set_voiture_tab_efficiency(voiture_tab* v, int i, int efficiency);
int get_voiture_tab_fast_charge(voiture_tab* v, int i);
void set_voiture_tab_fast_charge(voiture_tab* v, int i, int fast_charge);

int get_voiture_tab_capacity(voiture_tab* v, int i);
int get_voiture_tab_fast_charge_W(voiture_tab* v, int i);

#endif
