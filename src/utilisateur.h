#ifndef _UTILISATEUR_H_
#define _UTILISATEUR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "station.h"
#include "voiture.h"
#include "coord.h"
#include "a_star.h"
#include "selection.h"
#include "pota_file.h"
#include "chemin.h"
#define vitesse 80
#define ticksparh 6


struct utilisateur
{
    char* voiture;
    coord* depart; //lo=longitude, la=latitude
    coord* arrivee;
    struct utilisateur* next;
} typedef utilisateur;

struct utilisateurinfo
{
    int ID_courrant;
    int Nb_ticks_attente;
    chemin_tab_struct* chemin;
} typedef utilisateurinfo;

struct utilisateurtrajet
{
    utilisateurinfo* info;
    struct utilisateurtrajet* next;
} typedef utilisateurtrajet;

utilisateur* create_utilisateur();

utilisateur* rdm_utilisateur(voiture_tab* list_v, station_tab* list_s,int n);

utilisateurinfo* create_utilisateurinfo();

utilisateurtrajet* create_utilisateurtrajet();

utilisateurtrajet* trajets(utilisateur* list_u);

void utilisateur_trajet_append(utilisateurtrajet* trajet, utilisateurinfo* info);

void utilisateur_info_change(utilisateurinfo* info, chemin_tab_struct* chemin, int ID, int tic);

#endif
