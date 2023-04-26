#include "selection.h"
#include "pota_file.h"

int main(int argc, char** argv){
    // Suppression des warnings
    argc = 0;
    argv = NULL;

    station_tab* tab_s = read_csv_station_tab("BD/stations.csv");
    coord* depart = create_coord(48.856614, 2.3522219);
    coord* arrivee = create_coord(48.85, 2.35);
    double marge = 1;

    corresp_station_tab* corresp = select_point_struct(depart, arrivee, tab_s, marge);
    matrice_inf* matrice = generate_adj_matrice(corresp, depart, arrivee, tab_s);

    destroy_coord(depart);
    destroy_coord(arrivee);

    destroy_matrice_struc(matrice);
    destroy_corresp_tab(corresp);

    destroy_station_tab(tab_s);

}
