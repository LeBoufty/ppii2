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
#include "potagibus_a_star.h"
#include "selection.h"
#include "pota_file.h"

struct utilisateur
{
    char voiture;
    coord* depart; //lo=longitude, la=latitude
    coord* arrivee;
    utilisateur* next;
} typedef utilisateur;

struct utilisateurinfo
{
    chemin* chemin;
    double distance_pro;
    double taux_charge;
    utilisateurinfo* next;
} typedef utilisateurinfo;

struct utilisateurtrajet
{
    utilisateurinfo* info;
    utilisateurtrajet* next;
} typedef utilisateurtrajet;

utilisateur* create_utilisateur();

utilisateur* rdm_utilisateur(voiture_tab* list_v, station_tab* list_s,int n);

utilisateurinfo* create_utilisateurinfo();

utilisateurtrajet* create_utilisateurtrajet();

utilisateurtrajet* trajets(utilisateur* list_u);

#endif
