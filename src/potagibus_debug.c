#include "selection.h"
#include "pota_file.h"
#include "chemin.h"
#include "a_star.h"
#include <time.h>

int main(int argc, char** argv){
    // Suppression des warnings
    argc = 0;
    argv = NULL;

    voiture_tab* tab_v = read_csv_voiture_tab("BD/ev-data.csv");
    station_tab* tab_s = read_csv_station_tab("BD/stations.csv");
    coord* depart = create_coord();
    set_coord(depart, 51.01853808578892, 2.454941222555289);
    coord* arrivee = create_coord();
    set_coord(arrivee, 42.664455244199644, 2.8839045447890412);
    double marge = 1;
    printf("%d\n", size_station_tab(tab_s));
    corresp_station_tab* corresp = select_point_struct(depart, arrivee, tab_s, marge);
    printf("%d\n", size_corresp_tab(corresp));
    matrice_inf* matrice = generate_adj_matrice(corresp, depart, arrivee, tab_s);

    double dist = distance(depart, arrivee);
    printf("%f\n", dist);
    printf("caca\n");
    // print_matrice_struc(matrice);

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    chemin_tab_struct* chemin = a_star(matrice, corresp, tab_s, tab_v, 298, 0.33, 30, -1);
    print_chemin_tab_struct(chemin);
    destroy_chemin_tab_struct(chemin);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Temps d'exécution : %f\n", cpu_time_used);
    destroy_coord(depart);
    destroy_coord(arrivee);

    destroy_matrice_struc(matrice);
    destroy_corresp_tab(corresp);

    destroy_station_tab(tab_s);
    destroy_voiture_tab(tab_v);

}
