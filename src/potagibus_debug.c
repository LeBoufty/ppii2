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
    set_coord(depart, 43.15797922487215, -1.120695982008584);
    coord* arrivee = create_coord();
    set_coord(arrivee, 51.048093402957015, 2.4417101732651956);
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
    chemin_tab_struct* chemin = a_star(matrice, corresp, tab_s, tab_v, 298, 0.05, 80, -1);
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
