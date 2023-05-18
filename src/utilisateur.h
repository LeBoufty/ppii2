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
#include "matrice.h"
#define VITESSE 80
#define TICKSPARH 6
#define TEMPS_RECHARGE_MAX 2
#define MINIMUM_PERCENT_BATTERY 1
#define CAPACITE_DEPART 0


struct utilisateur
{
    int IDvoiture;
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

struct utilisateurtrajet_header
{
    utilisateurtrajet* first;
    int size;
}typedef utilisateurtrajet_header;

utilisateur* create_utilisateur();

utilisateur* rdm_utilisateur(voiture_tab* list_v, station_tab* list_s,int n);

utilisateurinfo* create_utilisateurinfo();

utilisateurtrajet* create_utilisateurtrajet();

utilisateurtrajet_header* create_utlisateurtrajet_header(utilisateurtrajet* trajet);

utilisateurtrajet* trajets(utilisateur* list_u, station_tab* tab_s, voiture_tab* tab_v);

utilisateurtrajet* destroy_utilisateur_trajet_chainon(utilisateurtrajet* currenttrajet, utilisateurtrajet* pasttrajet, utilisateurtrajet_header* header);//supprime le chainon et renvoie le trajet suivant

int get_size_utilisateurtrajet(utilisateurtrajet* trajet);

void utilisateur_trajet_append(utilisateurtrajet* trajet, utilisateurinfo* info);

void utilisateur_info_change(utilisateurinfo* info, chemin_tab_struct* chemin, int ID, int tic);

void destroy_utilisateur_trajet(utilisateurtrajet* trajet);

void destroy_utilisateur_info(utilisateurinfo* info);

void destroy_utilisateur(utilisateur* utilisateur);

#endif

