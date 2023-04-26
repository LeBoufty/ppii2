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

struct utilisateur
{
    char voiture;
    coord* depart; //lo=longitude, la=latitude
    coord* arrivee;
    utilisateur* next;
} typedef utilisateur;

utilisateur* create_utilisateur();
utilisateur* rdm_utilisateur(voiture_tab* list_v, station_tab* list_s,int n);

#endif
