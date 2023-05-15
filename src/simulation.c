#include "traitementP2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void createStationFile(int N,  station_tab* list_s) {
    char filename[30];
    sprintf(filename, "web/static/stations/%d.txt", N);
    FILE* file = fopen(filename, "a");
    for (int i=0;i<list_s->taille;i++){
        double a=get_station_tab_nbre_pdc_dispo(list_s,i)/get_station_tab_nbre_pdc(list_s,i);
        fprintf(file, "%f;", a);
    }
    fclose(file);  
}

void createCoordFile(station_tab* list_s){
    FILE* file=fopen("web/static/stations/coordonees","a");
    for (int i=0;i<list_s->taille;i++){
        fprintf(file, "%f,%f;",get_station_tab_coord_x(list_s,i),get_station_tab_coord_y(list_s,i));
    }
    fclose(file);
}

int main(int argc, char** argv){
    // Test du nombre d'arguments
    if(argc != 2){
        printf("Erreur : nombre d'arguments incorrect\n./simulation <Nb_utilisateurs>\n");
        return 1;
    }

    voiture_tab* tab_v = read_csv_voiture_tab("BD/ev-data.csv");
    station_tab* tab_s = read_csv_station_tab("BD/stations.csv");
    createCoordFile(tab_s);

    //Initialisation des utilisateurs
    int N=atoi(argv[1]);
    utilisateur* list_u=rdm_utilisateur(tab_v,tab_s,N);
    utilisateurtrajet* trajet=trajets(list_u);
    
    int i=0;
    while (trajet!=NULL){ //tant qu'il y a des utilisateurs qui ont un trajet
        createStationFile(i,tab_s);
        traitement(trajet);
        i++;
    }
    return 0;
}
//43.16477486861467,-1.1408199587551673,6
