#include "selection.h"

// Renvoie une liste des points qui sont dans une zone définie par deux points
list_int* select_point_list(coord* depart, coord* arrivee, station_tab* tab_s, int marge) {
    // On crée la liste des points
    list_int* liste = create_list_int();

    // On parcourt la liste des stations
    for (int i = 0; i < size_station_tab(tab_s); i++) {
        
        // On vérifie si la station est dans la zone
        if (excl_ovale(get_station_tab_coord(tab_s, i), depart, arrivee, marge)) {
            // Si oui, on l'ajoute à la liste
            append_list_int(liste, i);
        }   
    }

    // On renvoie la liste
    return liste;
}

// Renvoie un tableau de correspondance entre les indices de la liste et les indices de la matrice, utilise la liste des points en ajoutant les points de départ et d'arrivée
corresp_station_tab* select_point_struct(coord* depart, coord* arrivee, station_tab* tab_s, int marge) {
    // On récupère la liste des points
    list_int* liste = select_point_list(depart, arrivee, tab_s, marge);

    // On crée le tableau de correspondance
    corresp_station_tab* corresp = create_corresp_tab(size_list_int(liste) + 2);
    // On ajoute les points de départ et d'arrivée
    set_corresp_tab_id(corresp, 0, -1); // -1 correspond au point de départ
    set_corresp_tab_id(corresp, 1, -2); // -2 correspond au point d'arrivée

    // On remplit le tableau de correspondance
    for (int i = 2; i < size_corresp_tab(corresp); i++) {
        set_corresp_tab_id(corresp, i, pop_list_int(liste));
    }

    // On détruit la liste
    destroy_list_int(liste);

    // On renvoie le tableau de correspondance
    return corresp;
}

// Génère la matrice de distance entre les points sélectionnés en ajoutant les points de départ et d'arrivée
matrice_inf* generate_adj_matrice_corresp(corresp_station_tab* corresp, coord* depart, coord* arrivee, station_tab* tab_s) {
    // On crée la matrice
    matrice_inf* matrice = create_matrice_struc(size_corresp_tab(corresp));

    // Les points de départ et d'arrivée sont les deux premiers points de la matrice

    // On crée des points temporaires
    coord* point_1 = create_coord();
    coord* point_2 = create_coord();

    // On remplit la matrice
    for (int i = 0; i < size_matrice_struc(matrice); i++) {
        // Si on a le point de départ
        if (i == 0) {
            set_coord_x(point_1, get_coord_x(depart));
            set_coord_y(point_1, get_coord_y(depart));
        }

        // Si on a le point d'arrivée
        else if (i == 1) {
            set_coord_x(point_1, get_coord_x(arrivee));
            set_coord_y(point_1, get_coord_y(arrivee));
        }

        // Si on a un point de la liste
        else {
            // On récupère le point dans le tableau de correspondance
            set_coord_x(point_1, get_coord_x(get_station_tab_coord(tab_s, get_corresp_tab_id(corresp, i))));
            set_coord_y(point_1, get_coord_y(get_station_tab_coord(tab_s, get_corresp_tab_id(corresp, i))));
        }
        
        for (int j = 0; j < i; j++) {
            // Si on a le point de départ
            if (j == 0) {
                set_coord_x(point_2, get_coord_x(depart));
                set_coord_y(point_2, get_coord_y(depart));
            }

            // Si on a le point d'arrivée
            else if (j == 1) {
                set_coord_x(point_2, get_coord_x(arrivee));
                set_coord_y(point_2, get_coord_y(arrivee));
            }

            // Si on a un point de la liste
            else {
                // On récupère le point dans le tableau de correspondance
                set_coord_x(point_2, get_coord_x(get_station_tab_coord(tab_s, get_corresp_tab_id(corresp, j))));
                set_coord_y(point_2, get_coord_y(get_station_tab_coord(tab_s, get_corresp_tab_id(corresp, j))));
            }

            // On calcule la distance entre les deux points
            set_element_matrice_struc(matrice, i, j, distance(point_1, point_2));

        }
    }

    // On détruit les points temporaires
    destroy_coord(point_1);
    destroy_coord(point_2);

    // On renvoie la matrice
    return matrice;
}

// Génère la matrice de distance entre les points sélectionnés en ajoutant les points de départ et d'arrivée
matrice_inf* generate_adj_matrice(station_tab* tab_s) {
    // On crée la matrice
    matrice_inf* matrice = create_matrice_struc(size_station_tab(tab_s));

    // On crée des points temporaires
    coord* point_1 = create_coord();
    coord* point_2 = create_coord();

    // On remplit la matrice
    for (int i = 0; i < size_matrice_struc(matrice); i++) {

        set_coord_x(point_1, get_coord_x(get_station_tab_coord(tab_s, i)));
        set_coord_y(point_1, get_coord_y(get_station_tab_coord(tab_s, i)));
        
        for (int j = 0; j < i; j++) {

            set_coord_x(point_2, get_coord_x(get_station_tab_coord(tab_s, j)));
            set_coord_y(point_2, get_coord_y(get_station_tab_coord(tab_s, j)));

            // On calcule la distance entre les deux points
            set_element_matrice_struc(matrice, i, j, distance(point_1, point_2));

        }
    }

    // On détruit les points temporaires
    destroy_coord(point_1);
    destroy_coord(point_2);

    // On renvoie la matrice
    return matrice;
}
