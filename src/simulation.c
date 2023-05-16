#include "traitementP2.h"
#include "stationtxt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv){
    // Test du nombre d'arguments
    if(argc != 2){
        printf("Erreur : nombre d'arguments incorrect\n./simulation <Nb_utilisateurs>\n");
        return 1;
    }

    voiture_tab* tab_v = read_csv_voiture_tab("BD/ev-data.csv");
    station_tab* tab_s = read_csv_station_tab("BD/stations.csv");
    createCoordFile(tab_s); //Juque là, c'est bon

    //Initialisation des utilisateurs
    int N=atoi(argv[1]);
    utilisateur* list_u=rdm_utilisateur(tab_v,tab_s,N);
    printf("Utilisateurs initialisés\n");
    utilisateurtrajet* trajet=trajets(list_u,tab_s,tab_v);
    printf("Trajets initialisés\n");
    
    int i=0;
    while (trajet!=NULL){ //tant qu'il y a des utilisateurs qui ont un trajet
        printf("i=%d\n",i);
        printf("trajet->next=%p\n",trajet->next);
        createStationFile(i,tab_s);
        traitement(trajet);     
        i++;
    }
    return 0;
}
//43.16477486861467,-1.1408199587551673,6
