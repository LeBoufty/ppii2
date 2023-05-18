#include "utilisateur.h"


// Crée une liste d'utilisateur vide
utilisateur* create_utilisateur()
{
    utilisateur* list_u=malloc(sizeof(utilisateur));
    list_u->depart=create_coord();
    list_u->arrivee=create_coord();
    list_u->IDvoiture=0;
    list_u->next=NULL;
    return(list_u);
}

utilisateurinfo* create_utilisateurinfo()
{
    utilisateurinfo* list_ui=malloc(sizeof(utilisateurinfo));
    list_ui->Nb_ticks_attente=0;
    list_ui->ID_courrant=0;
    list_ui->chemin=NULL;
    return(list_ui);
}

utilisateurtrajet* create_utilisateurtrajet()
{
    utilisateurtrajet* list_ut=malloc(sizeof(utilisateurtrajet));
    list_ut->info=NULL;
    list_ut->next=NULL;
    return(list_ut);
}

// Crée une liste d'utilisateur remplie aléatoirement
utilisateur* rdm_utilisateur(voiture_tab* list_v, station_tab* list_s,int n) {
    utilisateur* list_u=create_utilisateur();
    float lodep, loarr, ladep, laarr;
    int taille_v=size_voiture_tab(list_v);
    int taille_s=size_station_tab(list_s);
    int rdm_v=0;
    int rdm_s_dep=0;
    int rdm_s_arr=0;
    int i=0;
    int IDvoiture;
    for (i=0;i<n;i++)
    {
        rdm_v=rand()%taille_v;
        rdm_s_dep=rand()%taille_s;
        rdm_s_arr=rand()%taille_s;
        lodep=get_station_tab_coord_x(list_s,rdm_s_dep);
        loarr=get_station_tab_coord_x(list_s,rdm_s_arr);
        ladep=get_station_tab_coord_y(list_s,rdm_s_dep);
        laarr=get_station_tab_coord_y(list_s,rdm_s_arr);
        IDvoiture=rdm_v;

        utilisateur* u_suiv = create_utilisateur();
        set_coord_x(u_suiv->depart,get_coord_x(list_u->depart));
        set_coord_y(u_suiv->depart,get_coord_y(list_u->depart));
        set_coord_x(u_suiv->arrivee,get_coord_x(list_u->arrivee));
        set_coord_y(u_suiv->arrivee,get_coord_y(list_u->arrivee));
        u_suiv->IDvoiture=list_u->IDvoiture;
        u_suiv->next=list_u->next;
        set_coord_y(list_u->arrivee,laarr);
        set_coord_y(list_u->depart,ladep);
        set_coord_x(list_u->arrivee,loarr);
        set_coord_x(list_u->depart,lodep);
        list_u->IDvoiture=IDvoiture;
        list_u->next=u_suiv;
    }
    return list_u;
}

void utilisateur_trajet_append(utilisateurtrajet* trajet, utilisateurinfo* info)
{
    utilisateurtrajet* traj_suiv = create_utilisateurtrajet();
    traj_suiv->info=trajet->info;
    trajet->info=info;
    traj_suiv->next=trajet->next;
    trajet->next=traj_suiv;
    
}

void utilisateur_info_change(utilisateurinfo* info, chemin_tab_struct* chemin, int ID, int tic)
{
    info->chemin=chemin;
    info->ID_courrant=ID;
    info->Nb_ticks_attente=tic;

}

utilisateurtrajet* trajets(utilisateur* list_u, station_tab* tab_s, voiture_tab* tab_v)
{
    utilisateurtrajet* trajet=create_utilisateurtrajet();
    int size;
    matrice_inf* matrice = generate_adj_matrice(tab_s);
    printf("matrice generee\n");
    while (list_u->next!=NULL)
    {
        utilisateurinfo* info=create_utilisateurinfo();
        chemin_tab_struct* chemin=a_star(matrice, list_u->depart, list_u->arrivee, tab_s, tab_v, list_u->IDvoiture,TEMPS_RECHARGE_MAX,MINIMUM_PERCENT_BATTERY, CAPACITE_DEPART);
        size=size_chemin_tab_struct(chemin);
        utilisateur_info_change(info,chemin,size_chemin_tab_struct(chemin)-1,get_chemin_tab_struct_distance_prochain(chemin,0)/VITESSE*TICKSPARH);
        printf("Distance prochain : %f\n",get_chemin_tab_struct_distance_prochain(chemin,0));
        utilisateur_trajet_append(trajet,info);
        printf("Trajet ajouté\n");
        list_u=list_u->next;
    }
    destroy_matrice_struc(matrice);
    return(trajet);
}

void destroy_utilisateur_trajet(utilisateurtrajet* trajet)
{
    if(trajet==NULL)
    {
        return;
    }
    destroy_utilisateur_info(trajet->info);
    free(trajet);

}

void destroy_utilisateur_trajet_list(utilisateurtrajet* trajet)
{
    if(trajet==NULL)
    {
        return;
    }
    utilisateurtrajet* traj_next=trajet->next;
    while (traj_next!=NULL)
    {
        destroy_utilisateur_trajet(trajet);
        free(trajet);
        trajet=traj_next;
        traj_next=traj_next->next;
    }
    destroy_utilisateur_info(trajet->info);
    free(trajet);
}


void destroy_utilisateur_info(utilisateurinfo* info)
{
    if(info==NULL)
    {
        return;
    }
    destroy_chemin_tab_struct(info->chemin);
    free(info);
}


void destroy_utilisateur(utilisateur* utilisateurs)
{
    if(utilisateurs==NULL)
    {
        return;
    }
    utilisateur* u_next=utilisateurs->next;
    while (u_next!=NULL)
    {
        destroy_coord(utilisateurs->depart);
        destroy_coord(utilisateurs->arrivee);
        free(utilisateurs);
        utilisateurs=u_next;
        u_next=u_next->next;
    }
    destroy_coord(utilisateurs->depart);
    destroy_coord(utilisateurs->arrivee);
    free(utilisateurs);
}

//supprime le chainon et renvoie le trajet suivant
utilisateurtrajet* destroy_utilisateur_trajet_chainon(utilisateurtrajet* currenttrajet, utilisateurtrajet* pasttrajet, utilisateurtrajet_header* header){
    if (pasttrajet!=NULL){
        currenttrajet=currenttrajet->next;
        destroy_utilisateur_trajet(pasttrajet->next);
        pasttrajet->next=currenttrajet;
        header->size--;
        return currenttrajet;
    }
    else{
        pasttrajet=currenttrajet->next;
        destroy_utilisateur_trajet(currenttrajet);
        header->first=pasttrajet;
        header->size--;
        return pasttrajet;
    }
}

utilisateurtrajet_header* create_utlisateurtrajet_header(utilisateurtrajet* trajet){
    utilisateurtrajet_header* header=malloc(sizeof(utilisateurtrajet_header));
    header->first=trajet;
    header->size=get_size_utilisateurtrajet(trajet);
    return header;
}

int get_size_utilisateurtrajet(utilisateurtrajet* trajet){
    if (trajet == NULL){ 
        return 0;
    }
    int size=-1;
    while (trajet!=NULL){
        size++;
        trajet=trajet->next;
    }
    return size;
}

void destroy_utilisateur_trajet_header(utilisateurtrajet_header* header){
    destroy_utilisateur_trajet_list(header->first);
    free(header);
}

