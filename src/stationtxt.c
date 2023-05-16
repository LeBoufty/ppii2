#include "station.h"

void createStationFile(int N,  station_tab* list_s){
    printf("createStationFile\n");
    char filename[30];
    sprintf(filename, "web/static/stations/%d.txt", N);
    FILE* file = fopen(filename, "a");
    for (int i=0;i<list_s->taille;i++){
        double a=get_station_tab_nbre_pdc_dispo(list_s,i)/get_station_tab_nbre_pdc(list_s,i);
        fprintf(file, "%f;", a);
    }
    fclose(file);  
    printf("createStationFile FIN\n");
}

void createCoordFile(station_tab* list_s){
    printf("createCoordFile\n");
    FILE* file=fopen("web/static/stations/coordonees","w");
    for (int i=0;i<list_s->taille;i++){
        fprintf(file, "%f,%f;",get_station_tab_coord_x(list_s,i),get_station_tab_coord_y(list_s,i));    
    }
    fclose(file);
    printf("createCoordFile FIN\n");
}
