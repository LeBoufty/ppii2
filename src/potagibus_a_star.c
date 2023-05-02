#include "potagibus_a_star.h"



// Algorithme A* pour trouver l'un des chemins les plus courts entre deux sommets
int* a_star(matrice_inf* mat_st, int depart, int arrivee, float distance_max){
    // Création du chemin de départ
    chemin* chemin_base = create_chemin();
    chemin* chemin_initial = push_chemin(chemin_base, depart, 0);

    // Création de la liste de garbage
    garbage_chemin* garbage_collector = create_garbage_chemin();
    push_garbage_chemin(garbage_collector, chemin_base);
    push_garbage_chemin(garbage_collector, chemin_initial);

    // Création de la file de priorité triée par distance
    file* file_priorite = create_file();
    enqueue_file(file_priorite, chemin_initial, depart, 0);

    // Création et initialisation du tableau des points visités
    int taille = taille_mat_struc(mat_st);
    bool* visite = malloc(sizeof(bool) * taille);
    for (int i = 0; i < taille; i++){
        visite[i] = false;
    }

    // Initialisation des variables temporaires
    chemin* chemin_tmp = NULL;
    int id_tmp = -1;
    float distance_approche_tmp = -1; // Variable inutile ici, mais nécessaire pour la file de priorité
    float distance_chemin_tmp = -1;

    // Début de l'algorithme A*
    while (!is_empty_file(file_priorite) && !is_next_file(file_priorite, arrivee)){
        // Récupération du premier élément de la file
        dequeue(file_priorite, &chemin_tmp, &id_tmp, &distance_approche_tmp);
        distance_chemin_tmp = distance_chemin(chemin_tmp);
        
        // Si le point est déjà visité, on ne le traite pas
        if (visite[id_tmp]){
            continue;
        }

        // On marque le point comme visité
        visite[id_tmp] = true;

        // On ajoute tous les points adjacents au point actuel dans la file
        for (int i = 0; i < taille; i++){
            float longueur = element_mat_struc(mat_st, id_tmp, i); // Distance entre le point actuel et le point i

            if (longueur <= distance_max && !visite[i]){ // Si le point n'est pas visité et qu'il est accessible

                chemin* chemin_tmp2 = push_chemin(chemin_tmp, i, longueur); // On crée un nouveau chemin
                push_garbage_chemin(garbage_collector, chemin_tmp2); // On ajoute le chemin à la liste de garbage
                float distance_approche = distance_chemin_tmp + longueur + LAMBDA * element_mat_struc(mat_st, i, arrivee); // Distance entre le point actuel et le point d'arrivée

                enqueue_file(file_priorite, chemin_tmp2, i, distance_approche); // On ajoute le point à la file
            }
        }
    }

    // Si la file est vide, on retourne NULL
    if (is_empty_file(file_priorite)){
        destroy_garbage_chemin(garbage_collector);
        destroy_file(file_priorite);
        free(visite);
        return NULL;
    }

    // Récupération du chemin le plus court
    dequeue(file_priorite, &chemin_tmp, &id_tmp, &distance_approche_tmp);
    int* chemin_final = copy_chemin(chemin_tmp);

    // Destruction des structures de données
    destroy_garbage_chemin(garbage_collector);
    destroy_file(file_priorite);
    free(visite);

    return chemin_final;
}


// Algorithme A* pour trouver l'un des chemins les plus courts entre deux sommets avancé
    
// }
