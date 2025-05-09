#include "traitementP2.h"
#include "stationtxt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char** argv){
    clock_t start, end;
    double Time;

    start = clock(); //Début du chrono

    // Test du nombre d'arguments
    if(argc != 2){
        printf("Erreur : nombre d'arguments incorrect\n./simulation <Nb_utilisateurs>\n");
        return 1;
    }

    if (atoi(argv[1])<1){
        printf("Erreur : nombre d'utilisateurs incorrect\n");
        return 1;
    }

    voiture_tab* tab_v = read_csv_voiture_tab("BD/ev-data.csv");
    station_tab* tab_s = read_csv_station_tab("BD/stations.csv");

    //Initialisation des utilisateurs
    int N=atoi(argv[1]);
    printf("Nombre d'utilisateurs : %d\n",N);
    utilisateur* list_u=rdm_utilisateur(tab_v,tab_s,N);
    printf("Utilisateurs initialisés\n");
    utilisateurtrajet* trajet=trajets(list_u,tab_s,tab_v);
    utilisateurtrajet_header* trajet_header=create_utlisateurtrajet_header(trajet);
    printf("Trajets initialisés\n--------------\n");
    
    int i=0;
    while (trajet_header->size>0){ //tant qu'il y a des utilisateurs qui ont un trajet
        printf("--------------------\ni=%d\n",i);
        createStationFile(i,tab_s);
        traitement(trajet_header);
        trajet=trajet_header->first; 
        i++;
        printf("Nombre d'utilisateurs : %d\n",trajet_header->size);
    }
    destroy_voiture_tab(tab_v);
    destroy_station_tab(tab_s);
    destroy_utilisateur_trajet_header(trajet_header);
    destroy_utilisateur(list_u);
    printf("FIN\n");

    end = clock(); //Arrêt du chrono

    Time = ((double) (end - start)) / CLOCKS_PER_SEC; // Calcul du temps d'exécution

    printf("Temps de calculs: %f secondes pour %d utilisateurs.\n Soit %f secondes par utilisateurs \n", Time,N,(double)Time/N);
    return 0;
}
//43.16477486861467,-1.1408199587551673,6
