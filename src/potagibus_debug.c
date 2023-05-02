#include "selection.h"
#include "pota_file.h"
#include "chemin.h"
#include "a_star.h"

int main(int argc, char** argv){
    // Suppression des warnings
    argc = 0;
    argv = NULL;

    voiture_tab* tab_v = read_csv_voiture_tab("BD/ev-data.csv");
    station_tab* tab_s = read_csv_station_tab("BD/stations.csv");
    coord* depart = create_coord();
    set_coord(depart, 48.692393357435655, 6.1835824482039214);
    coord* arrivee = create_coord();
    set_coord(arrivee, 49.119026828027536, 6.240734936284884);
    double marge = 50;
    printf("%d\n", size_station_tab(tab_s));
    corresp_station_tab* corresp = select_point_struct(depart, arrivee, tab_s, marge);
    printf("%d\n", size_corresp_tab(corresp));
    matrice_inf* matrice = generate_adj_matrice(corresp, depart, arrivee, tab_s);

    double dist = distance(depart, arrivee);
    printf("%f\n", dist);
    
    //print_matrice_struc(matrice);
    chemin_tab_struct* chemin = a_star(matrice, corresp, tab_s, tab_v, 0, 1, 5, -1);
    destroy_chemin_tab_struct(chemin);

    destroy_coord(depart);
    destroy_coord(arrivee);

    destroy_matrice_struc(matrice);
    destroy_corresp_tab(corresp);

    destroy_station_tab(tab_s);
    destroy_voiture_tab(tab_v);

    coord* a = create_coord();
    coord* b = create_coord();

    set_coord(a, 48.684557, 6.188514);
    set_coord(b, 48.689762, 6.173022);
    
    printf("%f\n", distance(a, b));

    destroy_coord(a);
    destroy_coord(b);    

}
