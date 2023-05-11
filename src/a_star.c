#include "a_star.h"

// Fonction min
double min(double a, double b){
    if(a < b){
        return a;
    }
    return b;
}

// Chemin to chemin_tab_struct
chemin_tab_struct* chemin_to_chemin_tab_struct(chemin* chemin, corresp_station_tab* corresp, station_tab* tab_s, voiture_tab* tab_v, int id_voiture){
    int taille = size_chemin(chemin);
    chemin_tab_struct* cts = create_chemin_tab_struct(taille, tab_s, tab_v, id_voiture);

    // Remplissage du chemin_tab_struct
    for(int i = 0; i < taille; i++){
        set_chemin_tab_struct_id_station(cts, i, get_corresp_tab_id(corresp, chemin -> id));
        set_chemin_tab_struct_distance_prochain(cts, i, chemin -> distance_prochain);
        set_chemin_tab_struct_capacite_avant(cts, i, chemin -> capacite_avant);
        set_chemin_tab_struct_capacite_apres(cts, i, chemin -> capacite_apres);
        chemin = chemin -> suivant;
    }
    return cts;
}

// Algorithme A* pour trouver l'un des chemins les plus courts entre deux sommets, en utilisant la structure chemin, en utilisant la puissance nominale des bornes et sans correspondance de station
chemin_tab_struct* a_star(matrice_inf* mat_st, coord* depart, coord* arrivee, station_tab* tab_s, voiture_tab* tab_v, int id_voiture, double temps_recharge_max, double minimum_percent_battery, double capacite_depart){
    // Crée le tableau de correspondance
    corresp_station_tab* corresp = select_point_struct(depart, arrivee, tab_s, MARGE);

    // Récupération de la capacité de la voiture si elle n'est pas donnée
    if (capacite_depart == -1 || capacite_depart == 0){
        capacite_depart = get_voiture_tab_capacity(tab_v, id_voiture);
    }

    // Création du garbage collector
    garbage_chemin* garbage_collector = create_garbage_chemin();

    // Création du chemin de départ
    chemin* chemin_base = create_chemin(garbage_collector);
    chemin* chemin_initial = push_chemin(chemin_base, 0, 0, capacite_depart, capacite_depart, garbage_collector);

    // Création de la file de priorité triée par distance
    file* file_priorite = create_file();
    enqueue_file(file_priorite, chemin_initial, 0);

    // Création du tableau des points visités
    visite_tab* visite = create_visite_tab(size_matrice_struc(mat_st));

    // Création des constantes de parcours
    double capacite_min = ((double) get_voiture_tab_capacity(tab_v, id_voiture)) * minimum_percent_battery / 100.0;

    // Boucle principale
    while (!is_empty_file(file_priorite) && !is_next_file(file_priorite,1)) {
        // Récupération du chemin courant
        chemin* chemin_courant = dequeue_file(file_priorite);
        int id_station_courant = get_chemin_id(chemin_courant);
        double distance_courant = get_chemin_distance_prochain(chemin_courant);
        
        // Si le point est déjà visité, on ne le traite pas
        if (get_visite_tab(visite, id_station_courant)){
            continue;
        }
        set_visite_tab(visite, id_station_courant, true);

        // Calcul de la distance maximale que l'on peut parcourir avec la batterie actuelle
        double distance_max = (get_chemin_capacite_apres(chemin_courant) - capacite_min) / ((double) get_voiture_tab_efficiency(tab_v, id_voiture));

        // On ajoute tous les points adjacents au point actuel dans la file
        for (int i = 0; i < size_matrice_struc(mat_st); i++) {
            // Si le point est déjà visité ou est le point courant, on ne le traite pas
            if (get_visite_tab(visite, i) || i == id_station_courant){
                continue;
            }

            double distance_i = get_element_matrice_struc(mat_st, id_station_courant, i);

            // Si la distance est inférieure à la distance maximale que l'on peut parcourir, on ajoute le point dans la file
            if (distance_i <= distance_max) {
                // Calcul des variables pour le chemin
                double capacite_avant = get_chemin_capacite_apres(chemin_courant) - distance_i * ((double) get_voiture_tab_efficiency(tab_v, id_voiture));
                double capacite_apres = min(get_voiture_tab_capacity(tab_v, id_voiture), capacite_avant + temps_recharge_max * ((double) get_voiture_tab_fast_charge_W(tab_v, id_voiture)) * ((double)get_station_tab_puissance(tab_s, i )) / 300000.0);

                chemin* chemin_courant_for = push_chemin(chemin_courant, i, distance_i, capacite_avant, capacite_apres, garbage_collector);

                double distance_recharge = (capacite_apres - capacite_avant) / get_voiture_tab_efficiency(tab_v, id_voiture);

                double distance_approche = distance_courant + distance_i + LAMBDA * get_element_matrice_struc(mat_st, i, 1) - distance_recharge;

                enqueue_file(file_priorite, chemin_courant_for, distance_approche);
            }

        }

    }
    
    // Si la file est vide, on retourne NULL
    if (is_empty_file(file_priorite)){
        destroy_garbage_chemin(garbage_collector);
        destroy_file(file_priorite);
        destroy_visite_tab(visite);
        return NULL;
    }

    // On récupère le chemin le plus court
    chemin* chemin_final = dequeue_file(file_priorite);
    chemin_tab_struct* cts = chemin_to_chemin_tab_struct(chemin_final, corresp, tab_s, tab_v, id_voiture);

    // On détruit les structures
    destroy_garbage_chemin(garbage_collector);
    destroy_file(file_priorite);
    destroy_visite_tab(visite);

    return cts;
}


// ANCIEN Ne marche plus | Algorithme A* pour trouver l'un des chemins les plus courts entre deux sommets, en utilisant la structure chemin_tab_struct
chemin_tab_struct* a_star_anc(matrice_inf* mat_st, corresp_station_tab* corresp, station_tab* tab_s, voiture_tab* tab_v, int id_voiture, double temps_recharge_max, double minimum_percent_battery, double capacite_depart){
    // Récupération de la capacité de la voiture si elle n'est pas donnée
    if (capacite_depart == -1 || capacite_depart == 0){
        capacite_depart = get_voiture_tab_capacity(tab_v, id_voiture);
    }

    // Création du garbage collector
    garbage_chemin* garbage_collector = create_garbage_chemin();

    // Création du chemin de départ
    chemin* chemin_base = create_chemin(garbage_collector);
    chemin* chemin_initial = push_chemin(chemin_base, 0, 0, capacite_depart, capacite_depart, garbage_collector);

    // Création de la file de priorité triée par distance
    file* file_priorite = create_file();
    enqueue_file(file_priorite, chemin_initial, 0);

    // Création du tableau des points visités
    visite_tab* visite = create_visite_tab(size_matrice_struc(mat_st));

    // Création des constantes de parcours
    double capacite_min = (double) get_voiture_tab_capacity(tab_v, id_voiture) * minimum_percent_battery / 100.0;

    // Boucle principale
    while (!is_empty_file(file_priorite) && !is_next_file(file_priorite,1)) {
        // Récupération du chemin courant
        chemin* chemin_courant = dequeue_file(file_priorite);
        int id_station_courant = get_chemin_id(chemin_courant);
        double distance_courant = get_chemin_distance_prochain(chemin_courant);
        
        // Si le point est déjà visité, on ne le traite pas
        if (get_visite_tab(visite, id_station_courant)){
            continue;
        }
        set_visite_tab(visite, id_station_courant, true);

        // Calcul de la distance maximale que l'on peut parcourir avec la batterie actuelle
        double distance_max = (get_chemin_capacite_apres(chemin_courant) - capacite_min) / get_voiture_tab_efficiency(tab_v, id_voiture);

        // On ajoute tous les points adjacents au point actuel dans la file
        for (int i = 0; i < size_matrice_struc(mat_st); i++) {
            // Si le point est déjà visité ou est le point courant, on ne le traite pas
            if (get_visite_tab(visite, i) || i == id_station_courant){
                continue;
            }

            double distance_i = get_element_matrice_struc(mat_st, id_station_courant, i);

            // Si la distance est inférieure à la distance maximale que l'on peut parcourir, on ajoute le point dans la file
            if (distance_i <= distance_max) {
                // Calcul des variables pour le chemin
                double capacite_avant = get_chemin_capacite_apres(chemin_courant) - distance_i * get_voiture_tab_efficiency(tab_v, id_voiture);
                double capacite_apres = min(get_voiture_tab_capacity(tab_v, id_voiture), capacite_avant + temps_recharge_max * get_voiture_tab_fast_charge_W(tab_v, id_voiture));

                chemin* chemin_courant_for = push_chemin(chemin_courant, i, distance_i, capacite_avant, capacite_apres, garbage_collector);

                double distance_approche = distance_courant + distance_i + LAMBDA * get_element_matrice_struc(mat_st, i, 1);

                enqueue_file(file_priorite, chemin_courant_for, distance_approche);
            }

        }

    }
    
    // Si la file est vide, on retourne NULL
    if (is_empty_file(file_priorite)){
        destroy_garbage_chemin(garbage_collector);
        destroy_file(file_priorite);
        destroy_visite_tab(visite);
        return NULL;
    }

    // On récupère le chemin le plus court
    chemin* chemin_final = dequeue_file(file_priorite);
    chemin_tab_struct* cts = chemin_to_chemin_tab_struct(chemin_final, corresp, tab_s, tab_v, id_voiture);

    // On détruit les structures
    destroy_garbage_chemin(garbage_collector);
    destroy_file(file_priorite);
    destroy_visite_tab(visite);

    return cts;
}

