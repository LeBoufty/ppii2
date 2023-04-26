#include "utilisateur.h"

// Crée une liste d'utilisateur vide
utilisateur* create_utilisateur()
{
    utilisateur* list_u=malloc(sizeof(utilisateur));
    list_u->depart=calloc(1,sizeof(coord));
    list_u->arrivee=calloc(1,sizeof(coord));
    list_u->voiture=calloc(1,sizeof(char));
    list_u->next=NULL;
    return(list_u);
}

// Crée une liste d'utilisateur remplie aléatoirement
utilisateur* rdm_utilisateur(voiture_tab* list_v, station_tab* list_s,int n) {
    utilisateur* list_u=utilisateur_create();
    float lodep, loarr, ladep, laarr;
    int taille_v=list_v->taille;
    int taille_s=list_s->taille;
    int rdm_v;
    int rdm_s_dep;
    int rdm_s_arr;
    int i;
    char* voiture;
    for (i=0;i<n;i++)
    {
        rdm_v==rand()%taille_v;
        rdm_s_dep==rand()%taille_s;
        rdm_s_arr==rand()%taille_s;
        lodep=get_station_tab_longitude(list_s,rdm_s_dep);
        loarr=get_station_tab_longitude(list_s,rdm_s_arr);
        ladep=get_station_tab_latitude(list_s,rdm_s_dep);
        laarr=get_station_tab_latitude(list_s,rdm_s_arr);
        voiture=get_voiture_tab_name(list_v,rdm_v);

        utilisateur* u_suiv = utilisateur_create();
        u_suiv->depart->x=list_u->depart->x;
        u_suiv->depart->y=list_u->depart->y;
        u_suiv->arrivee->x=list_u->arrivee->x;
        u_suiv->arrivee->y=list_u->arrivee->y;
        u_suiv->voiture=list_u->voiture;
        list_u->arrivee->y=laarr;
        list_u->depart->y=ladep;
        list_u->arrivee->x=loarr;
        list_u->depart->x=lodep;
        list_u->voiture=voiture;
        list_u->next=u_suiv;
    }
    return list_u;
}
