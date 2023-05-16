#include "traitementP2.h"


//Fonction qui passe le réseau à l'instant n+1
void traitement(utilisateurtrajet* trajet){
    utilisateurtrajet* currenttrajet=trajet;//Liste des utilisateurs
    utilisateurtrajet* lasttrajet=NULL;
    while (currenttrajet->next!=NULL){//Parcours tous les utilisateurs
        if (currenttrajet->info->Nb_ticks_attente<=0){//Si l'utilisateur est à une borne
            printf("ID courrant : %d\n",currenttrajet->info->ID_courrant);
            if (currenttrajet->info->ID_courrant==0){//Si l'utilisateur est à la fin du trajet
                printf("Utilisateur arrivé à destination\n");
                add_station_tab_nbre_pdc_dispo(currenttrajet->info->chemin->s_tab,get_chemin_tab_struct_id_station(currenttrajet->info->chemin,currenttrajet->info->ID_courrant-1), 1);//Libère la place dans la station
                currenttrajet=destroy_utilisateur_trajet_chainon(currenttrajet,lasttrajet);//Supprime l'utilisateur
                continue;
            }
            else{//Si sa station n'est pas la dernière
                if (currenttrajet->info->Nb_ticks_attente<0){//Si la voiture n'est pas chargée
                    printf("Voiture en charge\n");                                                                                                                     
                    currenttrajet->info->Nb_ticks_attente+=1;//Recharge la voiture 
                }
                else if (currenttrajet->info->Nb_ticks_attente==0){//Si la voiture est chargée
                printf("Voiture chargée\n");
                add_station_tab_nbre_pdc_dispo(currenttrajet->info->chemin->s_tab,get_chemin_tab_struct_id_station(currenttrajet->info->chemin,currenttrajet->info->ID_courrant-1), 1);//Libère la place dans la station
                currenttrajet->info->ID_courrant-=1;//Change de destination
                currenttrajet->info->Nb_ticks_attente=get_chemin_tab_struct_distance_prochain(currenttrajet->info->chemin,currenttrajet->info->ID_courrant-1)/TICKSPARH-1;//Se déplace vers sa destination
                }
            }
        }
        else if (currenttrajet->info->Nb_ticks_attente==1){//Si il arrive à une station
            printf("Utilisateur arrive à une station\n");
                if (get_station_tab_nbre_pdc_dispo(currenttrajet->info->chemin->s_tab,get_chemin_tab_struct_id_station(currenttrajet->info->chemin,currenttrajet->info->ID_courrant-1))>0){//Regarde si il y a de la place dans la station
                    printf("Utilisateur à une station\n");
                    currenttrajet->info->Nb_ticks_attente=-ceil(get_chemin_tab_struct_temps_recharge(currenttrajet->info->chemin,currenttrajet->info->ID_courrant-1)/TICKSPARH)+1;//Initialise le rechargement
                    add_station_tab_nbre_pdc_dispo(currenttrajet->info->chemin->s_tab,get_chemin_tab_struct_id_station(currenttrajet->info->chemin,currenttrajet->info->ID_courrant-1), -1);//Réserve sa place dans la station
                }
        }
        else currenttrajet->info->Nb_ticks_attente-=1;//Si à une distance>1 d'une station
    printf("currenttrajet->info->Nb_ticks_attente=%d\n",currenttrajet->info->Nb_ticks_attente);
    lasttrajet=currenttrajet;//Utilisé pour supprimer un utilisateur
    currenttrajet=currenttrajet->next;//Prochain utilisateur
    printf("Utilisateur suivant\n");
    printf("-------\n");
    }
}
/*
  -traitement(info: utilisateurinfo*)->Etat_reseau int* (Grosse fonction)
	  Utilité : Parcours la liste chainée pour trouver les utilisateur à une distance_de_borne=0, gère les différents cas (Lance le rechargement, file d'attente ou fin de trajet.), gère le rechargement et gère le prochain tick. En gros, elle gère tout le tick de 10min en faisant 1 seul parcours de la liste.
	  I/O 	Entrée : list_truc la liste des trajets avec leur distance_de_borne
		      Sortie : retourne l'état du réseau à l'instant n 

*/
