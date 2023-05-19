#include "traitementP2.h"


//Fonction qui passe le réseau à l'instant n+1
void traitement(utilisateurtrajet_header* trajet_header){
    utilisateurtrajet* trajet=trajet_header->first;
    utilisateurtrajet* currenttrajet=trajet;//Liste des utilisateurs
    utilisateurtrajet* lasttrajet=NULL;
    printf("Traitement\n");
    while (currenttrajet->next!=NULL){//Parcours tous les utilisateurs
        if (currenttrajet->info->chemin==NULL){
            printf("Utilisateur sans chemin\n");
            currenttrajet=destroy_utilisateur_trajet_chainon(currenttrajet,lasttrajet,trajet_header);//Supprime l'utilisateur
            printf("Utilisateur supprimé\n");
            if (currenttrajet==NULL)//Si il n'y a plus d'utilisateurs
                break;
            continue;
        }
        int id_station=get_chemin_tab_struct_id_station(currenttrajet->info->chemin,currenttrajet->info->ID_courrant);   
        printf("ID courrant %d\n",currenttrajet->info->ID_courrant);
        printf("Nb_ticks_attente %d\n",currenttrajet->info->Nb_ticks_attente);
        printf("ID station %d\n",id_station);
        printf("-\n");
        if (currenttrajet->info->Nb_ticks_attente<=0){//Si l'utilisateur est à une borne
            if (currenttrajet->info->Nb_ticks_attente<0){//Si la voiture n'est pas chargée                                                                                                                     
                currenttrajet->info->Nb_ticks_attente+=1;//Recharge la voiture 
            }
            else if (currenttrajet->info->Nb_ticks_attente==0){//Si la voiture est chargée
                printf("Voiture chargée\n");
                if (id_station!=-1 && id_station!=-2) {//Si l'utilisateur n'est pas à la fin du trajet ou au début
                    add_station_tab_nbre_pdc_dispo(currenttrajet->info->chemin->s_tab,get_chemin_tab_struct_id_station(currenttrajet->info->chemin,currenttrajet->info->ID_courrant), 1);//Libère la place dans la station
                    printf("Place libérée\n");
                }
                else if (id_station==-2){
                    printf("Utilisateur arrivé à destination\n");
                    currenttrajet=destroy_utilisateur_trajet_chainon(currenttrajet,lasttrajet,trajet_header);//Supprime l'utilisateur
                    if (currenttrajet==NULL)//Si il n'y a plus d'utilisateurs
                        break;
                    continue;
                }
                currenttrajet->info->ID_courrant-=1;//Change de destination
                currenttrajet->info->Nb_ticks_attente=get_chemin_tab_struct_distance_prochain(currenttrajet->info->chemin,currenttrajet->info->ID_courrant)/TICKSPARH-1;//Se déplace vers sa destination
                printf("Utilisateur en déplacement\n");
            }
        }
        else if (currenttrajet->info->Nb_ticks_attente==1){//Si il arrive à une station
            printf("Utilisateur arrivé à une station\n");
            if (id_station==-1){//Départ
                currenttrajet->info->ID_courrant-=1;//Change de destination
                currenttrajet->info->Nb_ticks_attente=get_chemin_tab_struct_distance_prochain(currenttrajet->info->chemin,currenttrajet->info->ID_courrant)/TICKSPARH-1;//Se déplace vers sa destination
                printf("Utilisateur en déplacement\n"); 
            }
            else if (id_station==-2){//Arrivée
                printf("Utilisateur arrivé à destination\n");
                currenttrajet=destroy_utilisateur_trajet_chainon(currenttrajet,lasttrajet,trajet_header);//Supprime l'utilisateur
                if (currenttrajet==NULL)//Si il n'y a plus d'utilisateurs
                    break;
                continue;
            }
            else if (get_station_tab_nbre_pdc_dispo(currenttrajet->info->chemin->s_tab,id_station)>0){//Si il y a une place dans la station
                printf("Utilisateur en attente\n");
                currenttrajet->info->Nb_ticks_attente=-ceil(get_chemin_tab_struct_temps_recharge(currenttrajet->info->chemin,currenttrajet->info->ID_courrant)*TICKSPARH)+1;//Initialise le rechargement
                add_station_tab_nbre_pdc_dispo(currenttrajet->info->chemin->s_tab,id_station, -1);//Réserve sa place dans la station
            }
        }
        else currenttrajet->info->Nb_ticks_attente-=1;//Si à une distance>1 d'une station
    printf("Utilisateur suivant\n");
    lasttrajet=currenttrajet;//Utilisé pour supprimer un utilisateur
    currenttrajet=currenttrajet->next;//Prochain utilisateur
    }
}
/*
  -traitement(info: utilisateurinfo*)->Etat_reseau int* (Grosse fonction)
	  Utilité : Parcours la liste chainée pour trouver les utilisateur à une distance_de_borne=0, gère les différents cas (Lance le rechargement, file d'attente ou fin de trajet.), gère le rechargement et gère le prochain tick. En gros, elle gère tout le tick de 10min en faisant 1 seul parcours de la liste.
	  I/O 	Entrée : list_truc la liste des trajets avec leur distance_de_borne
		      Sortie : retourne l'état du réseau à l'instant n 

*/
