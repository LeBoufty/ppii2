#include "selection.h"
#include "pota_file.h"

int main(int argc, char** argv){
    // Suppression des warnings
    argc = 0;
    argv = NULL;

    station_tab* tab_s = read_csv_station_tab("BD/stations.csv");
    coord* depart = create_coord();
    set_coord(depart, 48.89880886438817, 7.838002707088477);
    coord* arrivee = create_coord();
    set_coord(arrivee, 43.72682013364305, -0.9193429353112762);
    double marge = 50;
    printf("%d\n", size_station_tab(tab_s));
    corresp_station_tab* corresp = select_point_struct(depart, arrivee, tab_s, marge);
    printf("%d\n", size_corresp_tab(corresp));
    matrice_inf* matrice = generate_adj_matrice(corresp, depart, arrivee, tab_s);

    double dist = distance(depart, arrivee);
    printf("%f\n", dist);

    destroy_coord(depart);
    destroy_coord(arrivee);

    destroy_matrice_struc(matrice);
    destroy_corresp_tab(corresp);

    destroy_station_tab(tab_s);

}
