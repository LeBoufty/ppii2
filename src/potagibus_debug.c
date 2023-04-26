#include "selection.h"
#include "pota_file.h"

int main(int argc, char** argv){
    // Suppression des warnings
    argc = 0;
    argv = NULL;

    station_tab* tab_s = read_csv_station_tab("BD/stations.csv");
    destroy_station_tab(tab_s);

}
