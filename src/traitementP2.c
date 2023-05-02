#include "traitementP2.h"


//Fonction qui passe le réseau à l'instant n+1
int* traitement(utilisateurtrajet* trajet){
    utilisateurtrajet* currenttrajet=trajet;
    while (currenttrajet->next!=NULL){
        if (currenttrajet->info->distance_pro==0){//Si l'utilisateur est à une borne
            if (){//Si l'utilisateur est à la fin du trajet
            }
            if(){//Si il y a de la place dans la station
                //Mettre à jour la station    
                if (){//Si la voiture n'est pas chargée                                                                                                                      
                    if (){//Si la voiture est chargée pendant le tick
                        
                    }
                    else{//Si la voiture n'est pas chargée pendant le tick
                    }
                }
                else if (){//Si la voiture est chargée
                //Mettre à jour la station
                //enlever le point actuel et passer au prochain
                //Changer la distance_pro (-1 car c'est un tick)
                }
            }
        }
        else {//Si il n'est pas à une borne 
            currenttrajet->info->distance_pro=currenttrajet->info->distance_pro-1;
        }
    }
}

/*
  -traitement(info: utilisateurinfo*)->Etat_reseau int* (Grosse fonction)
	  Utilité : Parcours la liste chainée pour trouver les utilisateur à une distance_de_borne=0, gère les différents cas (Lance le rechargement, file d'attente ou fin de trajet.), gère le rechargement et gère le prochain tick. En gros, elle gère tout le tick de 10min en faisant 1 seul parcours de la liste.
	  I/O 	Entrée : list_truc la liste des trajets avec leur distance_de_borne
		      Sortie : retourne l'état du réseau à l'instant n 

Chemin ?

Peut-être faire un taux de charge comme : km_restant; km_total; vitesse_de_rechragement(en km/tick)

Liste d'attente ? Liste des files d'attentes /stations ? Liste de tableau des stations ? 

Prochaine étape ? cf chemin à emprunter
*/