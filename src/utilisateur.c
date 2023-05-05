#include "utilisateur.h"
#define vitesse 80
#define tiksparh 6

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

utilisateurinfo* create_utilisateurinfo()
{
    utilisateurinfo* list_ui=malloc(sizeof(utilisateurinfo));
    list_ui->Nb_ticks_attente=calloc(1,sizeof(int));
    list_ui->ID_courrant=calloc(1,sizeof(int));
    list_ui->chemin=calloc(1,sizeof(chemin_tab_struct));
    list_ui->next=NULL;
    return(list_ui);
}

utilisateurtrajet* create_utilisateurtrajet()
{
    utilisateurtrajet* list_ut=malloc(sizeof(utilisateurtrajet));
    list_ut->info=calloc(1,sizeof(utilisateurinfo));
    list_ut->next=NULL;
    return(list_ut);
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

void utilisateur_trajet_append(utilisateurtrajet* trajet, utilisateurinfo* info)
{
    utilisateurtrajet* traj_suiv = create_utilisateurtrajet();
    traj_suiv->info=trajet->info;
    trajet->info=info;
    trajet->next=traj_suiv;
    
}

void utilisateur_info_append(utilisateurinfo* info, chemin_tab_struct* chemin, int ID, int tic)
{
    utilisateurinfo* info_suiv=create_utilisateurinfo();
    info_suiv->chemin=info->chemin;
    info_suiv->ID_courrant=info->ID_courrant;
    info_suiv->Nb_ticks_attente=info->Nb_ticks_attente;
    info->chemin=chemin;
    info->ID_courrant=ID;
    info->Nb_ticks_attente=tic;
    info->next=info_suiv;
}

utilisateurtrajet* trajets(utilisateur* list_u)
{
    station_tab* tab_s = read_csv_station_tab("BD/stations.csv");
    utilisateurtrajet* trajet=create_utilisateurtrajet();
    int i=0;
    int size;
    while (list_u->next!=NULL)
    {
        utilisateurinfo* info=create_utilisateurinfo();
        corresp_station_tab* corresp = select_point_struct(list_u->depart, list_u->arrivee, tab_s, 1);
        matrice_inf* matrice = generate_adj_matrice(corresp, list_u->depart, list_u->arrivee, tab_s);
        chemin_tab_struct* chemin=a_star(matrice,list_u->depart,list_u->arrivee,50);
        size=size_chemin_tab_struct(chemin);
        utilisateur_info_append(info,chemin[1:],get_chemin_tab_struct_id_station(chemin,0),get_chemin_tab_struct_distance_prochain(chemin,0)*vitesse/tiksparh);
        utilisateur_trajet_append(trajet,info);
        list_u=list_u->next;
    }
    return(trajet);
}

