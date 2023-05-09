#include "traitementP2.h"


//Fonction qui passe le réseau à l'instant n+1
int* traitement(utilisateurtrajet* trajet){
    utilisateurtrajet* currenttrajet=trajet;
    while (currenttrajet->next!=NULL){
        if (currenttrajet->info->Nb_ticks_attente<=0){//Si l'utilisateur est à une borne
            if (currenttrajet->info->ID_courrant==0){//Si l'utilisateur est à la fin du trajet
                //destroy trajets
            }
            else{//Si sa station n'est pas la dernière
                if (currenttrajet->info->Nb_ticks_attente<0){//Si la voiture n'est pas chargée                                                                                                                      
                    currenttrajet->info->Nb_ticks_attente+=1;
                }
                else if (currenttrajet->info->Nb_ticks_attente==0){//Si la voiture est chargée
                add_station_tab_nbre_pdc_dispo(currenttrajet->info->chemin->s_tab,get_station_tab_id(currenttrajet->info->chemin->s_tab,currenttrajet->info->ID_courrant), 1);//Libère la place dans la station
                currenttrajet->info->ID_courrant-=1;//Change de destination
                currenttrajet->info->Nb_ticks_attente=get_chemin_tab_struct_distance_prochain(currenttrajet->info->chemin,currenttrajet->info->ID_courrant)-1;//Se déplace vers sa destination
                }
            }
        }
        else if (currenttrajet->info->Nb_ticks_attente-1<=0){
                if (get_station_tab_nbre_pdc_dispo(currenttrajet->info->chemin->s_tab,get_station_tab_id(currenttrajet->info->chemin->s_tab,currenttrajet->info->ID_courrant))>0){
                    currenttrajet->info->Nb_ticks_attente=get_chemin_tab_struct_temps_recharge(currenttrajet->info->chemin,currenttrajet->info->ID_courrant);
                    add_station_tab_nbre_pdc_dispo(currenttrajet->info->chemin->s_tab,get_station_tab_id(currenttrajet->info->chemin->s_tab,currenttrajet->info->ID_courrant), -1)
                }
        }
        else currenttrajet->info->Nb_ticks_attente-=1;
    }
}
/*
  -traitement(info: utilisateurinfo*)->Etat_reseau int* (Grosse fonction)
	  Utilité : Parcours la liste chainée pour trouver les utilisateur à une distance_de_borne=0, gère les différents cas (Lance le rechargement, file d'attente ou fin de trajet.), gère le rechargement et gère le prochain tick. En gros, elle gère tout le tick de 10min en faisant 1 seul parcours de la liste.
	  I/O 	Entrée : list_truc la liste des trajets avec leur distance_de_borne
		      Sortie : retourne l'état du réseau à l'instant n 

*/