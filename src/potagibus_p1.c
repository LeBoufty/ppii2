#include "selection.h"
#include "pota_file.h"
#include "chemin.h"
#include "a_star.h"
#include "coord.h"

// Programme qui renvoie la liste des stations et le temps de recharge pour un point de départ, un point d'arrivée, l'identifiant d'une voiture, le pourcentage minimal de batterie, le temps de recharge maximal en heures
// ./programe_name <lat_depart> <long_depart> <lat_arrivee> <long_arrivee> <id_voiture> <pourcentage_minimal_batterie> <temps_recharge_maximal>
int main(int argc, char** argv){
    // Test du nombre d'arguments
    if(argc != 8){
        printf("Erreur : nombre d'arguments incorrect\n./programe_name <lat_depart> <long_depart> <lat_arrivee> <long_arrivee> <id_voiture> <pourcentage_minimal_batterie> <temps_recharge_maximal>\n");
        return 1;
    }

    // Récupération des arguments
    double lat_depart = atof(argv[1]);
    double long_depart = atof(argv[2]);
    double lat_arrivee = atof(argv[3]);
    double long_arrivee = atof(argv[4]);
    int id_voiture = atoi(argv[5]);
    double pourcentage_minimal_batterie = atof(argv[6]);
    double temps_recharge_maximal = atof(argv[7]);

    // Création des coordonnées de départ et d'arrivée
    coord* depart = create_coord();
    set_coord(depart, long_depart, lat_depart);
    coord* arrivee = create_coord();
    set_coord(arrivee, long_arrivee, lat_arrivee);

    // Lecture des fichiers csv
    voiture_tab* tab_v = read_csv_voiture_tab("BD/ev-data.csv");
    station_tab* tab_s = read_csv_station_tab("BD/stations.csv");

    // Génération de la matrice d'adjacence
    matrice_inf* matrice = generate_adj_matrice(tab_s);

    // Recherche du chemin
    chemin_tab_struct* chemin = a_star(matrice, depart, arrivee, tab_s, tab_v, id_voiture, temps_recharge_maximal, pourcentage_minimal_batterie, -1);

    // Si le chemin n'existe pas
    if(chemin == NULL){
        printf("Erreur : chemin non trouvé\n");
        // Destruction des structures
        destroy_coord(depart);
        destroy_coord(arrivee);
        destroy_voiture_tab(tab_v);
        destroy_station_tab(tab_s);
        destroy_matrice_struc(matrice);
        return 1;
    }

    // Affichage du chemin
    int j = 1;
    printf("Numéro de la station : Nom de la station (latitude, longitude) Temps de rechargement\n");
    for (int i = size_chemin_tab_struct(chemin) - 2; i >= 1; i--){
        printf("Station n°%d :", j);
        printf("%s ", get_station_tab_id(tab_s, get_chemin_tab_struct_id_station(chemin, i)));
        printf("(%f, %f) ", get_station_tab_coord_y(tab_s, get_chemin_tab_struct_id_station(chemin, i)), get_station_tab_coord_x(tab_s, get_chemin_tab_struct_id_station(chemin, i)));
        printf("%f\n", get_chemin_tab_struct_temps_recharge(chemin, i));
        j++;
    }

    // Destruction des structures
    destroy_chemin_tab_struct(chemin);
    destroy_coord(depart);
    destroy_coord(arrivee);
    destroy_matrice_struc(matrice);
    destroy_station_tab(tab_s);
    destroy_voiture_tab(tab_v);

    return 0;
}
