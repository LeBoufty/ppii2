//#include "utilisateur.h"
#include "pota_file.h"

int main(int argc, char** argv){
    // Suppression des warnings
    argc = 0;
    argv = NULL;
    voiture_tab* tab_v = read_csv_voiture_tab("BD/ev-data.csv");
    station_tab* tab_s = read_csv_station_tab("BD/stations.csv");

    destroy_voiture_tab(tab_v);
    destroy_station_tab(tab_s);

    return 0;
}