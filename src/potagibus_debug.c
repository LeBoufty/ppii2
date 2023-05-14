#include "selection.h"
#include "pota_file.h"
#include "chemin.h"
#include "a_star.h"
#include <time.h>
#include "coord.h"

int main(int argc, char** argv){
    // Suppression des warnings
    argc = 0;
    argv = NULL;

    voiture_tab* tab_v = read_csv_voiture_tab("BD/ev-data.csv");
    station_tab* tab_s = read_csv_station_tab("BD/stations.csv");
    coord* depart = create_coord();
    set_coord(depart, 51.01853808578892, 2.454941222555289); // A inverser
    coord* arrivee = create_coord();
    set_coord(arrivee, 42.664455244199644, 2.8839045447890412); // A inverser
    printf("Coordonnées à inverser\n");

    matrice_inf* matrice = generate_adj_matrice(tab_s);
    double dist = distance(depart, arrivee);
    printf("%f\n", dist);
    printf("caca\n");
    // print_matrice_struc(matrice);

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    chemin_tab_struct* chemin = a_star(matrice, depart, arrivee, tab_s, tab_v, 0 , 0.50, 20, -1);
    printf("taille chemin : %d\n", size_chemin_tab_struct(chemin));
    print_chemin_tab_struct(chemin);
    destroy_chemin_tab_struct(chemin);
    double distan = distance(depart, arrivee);
    printf("distance : %f\n", distan);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Temps d'exécution : %f\n", cpu_time_used);
    destroy_coord(depart);
    destroy_coord(arrivee);

    destroy_matrice_struc(matrice);

    destroy_station_tab(tab_s);
    destroy_voiture_tab(tab_v);

}
