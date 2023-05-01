#include "selection.h"
#include "pota_file.h"
#include "chemin.h"

int main(int argc, char** argv){
    // Suppression des warnings
    argc = 0;
    argv = NULL;

    voiture_tab* tab_v = read_csv_voiture_tab("BD/ev-data.csv");
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

    chemin_tab_struct* cts = create_chemin_tab_struct(size_corresp_tab(corresp), tab_s, tab_v, 0);
    destroy_chemin_tab_struct(cts);

    destroy_coord(depart);
    destroy_coord(arrivee);

    destroy_matrice_struc(matrice);
    destroy_corresp_tab(corresp);

    destroy_station_tab(tab_s);
    destroy_voiture_tab(tab_v);

}
