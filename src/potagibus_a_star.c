#include "potagibus_a_star.h"

// Création d'un chemin vide
chemin* create_chemin(){ 
    chemin* c = malloc(sizeof(chemin));
    c -> id = -1;  
    // Les derniers éléments du chemin sont toujours NULL
    c -> suivant = NULL;
    c -> distance = 0;
    return c;
}

// Ajout d'un élément au chemin en tête de liste
chemin* push_chemin(chemin* c, int id, float distance){ 
    // Si le chemin n'existe pas, on ne fait rien
    if (c == NULL){ 
        return NULL;
    }

    // Création d'un nouvel élément
    chemin* new = create_chemin(); 
    new -> id = id;
    new -> suivant = c;
    new -> distance = distance + c -> distance;
    return new;
}

// Taille d'un chemin
int taille_chemin(chemin* c){ 
    // Si le chemin n'existe pas, retourne 0
    if (c == NULL){ 
        return 0;
    }

    // Parcours du chemin pour compter le nombre d'éléments
    int taille = 0;
    while (c != NULL){
        taille++;
        c = c -> suivant;
    }
    return taille;
}

// Distance d'un chemin
float distance_chemin(chemin* c){ 
    // Si le chemin n'existe pas, retourne 0
    if (c == NULL){ 
        return 0;
    }

    return c -> distance;
}

// Copie d'un chemin en un tableau d'entiers géré dynamiquement
int* copy_chemin(chemin* c){ 
    // Si le chemin n'existe pas, on ne fait rien
    if (c == NULL){ 
        return NULL;
    }

    // Création d'un tableau dynamique
    int taille = taille_chemin(c);
    int* tab = malloc(sizeof(int) * taille);

    // Copie du chemin dans le tableau
    for (int i = 0; i < taille; i++){ 
        tab[i] = c -> id;
        c = c -> suivant;
    }
    return tab;
}

// Destruction d'un chemin et de tous ses éléments | Non utilisé, utilisé destroy_garbage_chemin
void destroy_chemin(chemin* c){ 
    // Si le chemin n'existe pas, on ne fait rien
    if (c == NULL){ 
        return;
    }

    // Destruction de tous les éléments du chemin
    chemin* tmp = c;
    while (c != NULL){
        tmp = c;
        c = c -> suivant;
        free(tmp);
    }
}

// Création d'une liste de garbage vide
garbage_chemin* create_garbage_chemin(){ 
    garbage_chemin* g = malloc(sizeof(garbage_chemin));
    g -> taille = 0;
    g -> taille_max = INITIAL_SIZE;
    g -> chemin = malloc(sizeof(chemin*) * g -> taille_max);
    return g;
}

// Ajout d'un élément à la liste de garbage
void push_garbage_chemin(garbage_chemin* g, chemin* c){ 
    // Si la liste de garbage n'existe pas, on ne fait rien
    if (g == NULL){ 
        return;
    }

    // Si la liste de garbage est pleine, on la redimensionne
    if (g -> taille == g -> taille_max){ 
        g -> taille_max *= 2;
        g -> chemin = realloc(g -> chemin, sizeof(chemin*) * g -> taille_max);
    }

    // Ajout de l'élément à la liste de garbage
    g -> chemin[g -> taille] = c; 
    g -> taille++;
    return;
}

// Destruction de la liste de garbage
void destroy_garbage_chemin(garbage_chemin* g){ 
    // Si la liste de garbage n'existe pas, on ne fait rien
    if (g == NULL){ 
        return;
    }

    // Destruction de tous les éléments de la liste de garbage
    for (int i = 0; i < g -> taille; i++){ 
        free(g -> chemin[i]);
    }
    free(g -> chemin);
    free(g);
    return;
}

// Création d'une file de priorité triée par distance
file* create_file(){ 
    file* f = malloc(sizeof(file));
    f -> id = -1;
    f -> distance_approche = -1;
    // Les premiers éléments de la file sont toujours NULL
    f -> chemin = NULL; 
    f -> suivant = NULL;
    f -> precedent = NULL;
    return f;
}

// Ajout d'un élément dans la file de priorité triée par distance
void enqueue_file(file* f, chemin* c, int id, float distance_approche){ 
    // Si la file n'existe pas, on ne fait rien
    if (f == NULL){ 
        return;
    }

    // Création d'un nouvel élément
    file* new = create_file(); 
    new -> id = id;
    new -> distance_approche = distance_approche;
    new -> chemin = c;

    // Création d'un pointeur temporaire pour parcourir la file
    file* tmp = f; 
    while (tmp -> suivant != NULL && tmp -> suivant -> distance_approche < distance_approche){
        tmp = tmp -> suivant;
    }

    // Insertion de l'élément dans la file
    new -> suivant = tmp -> suivant; 
    new -> precedent = tmp;
    if (tmp -> suivant != NULL){
        file* tmp_suivant = tmp -> suivant; 
        tmp_suivant -> precedent = new;
    }
    tmp -> suivant = new;

    return;
}

// Retire le premier élément de la file
void dequeue(file* f, chemin** c, int* id, float* distance_approche){
    // Si la file n'existe pas, on ne fait rien
    if (f == NULL){
        return;
    }

    // Si la file est vide, on ne fait rien
    if (f -> suivant == NULL){ 
        return;
    }

    // Récupération des informations du premier élément de la file
    file* tmp = f -> suivant; 
    *c = tmp -> chemin; 
    *id = tmp -> id;
    *distance_approche = tmp -> distance_approche;

    // Suppression du premier élément de la file
    f -> suivant = tmp -> suivant;
    if (tmp -> suivant != NULL){
        file* tmp_suivant = tmp -> suivant;
        tmp_suivant -> precedent = f;
    }
    free(tmp);

    return;
}

// Retourne true si la file est vide, false sinon
bool is_empty_file(file* f){
    // Si la file n'existe pas ou est vide, on retourne true
    if (f == NULL){
        return true;
    }
    if (f -> suivant == NULL){
        return true;
    }

    return false;
}

// Retourne true si le premier élément de la file a l'id recherché, false sinon
bool is_next_file(file* f, int id){
    // Si la file n'existe pas ou est vide, on retourne false
    if (f == NULL){
        return false;
    }
    if (f -> suivant == NULL){
        return false;
    }

 
    if (f -> suivant -> id == id){
        return true;
    }

    return false;
}

// Destruction de la file
void destroy_file(file* f){
    // Si la file n'existe pas, on ne fait rien
    if (f == NULL){
        return;
    }

    // Destruction de tous les éléments de la file 
    file* tmp = f;
    while (f != NULL){
        tmp = f;
        f = f -> suivant;
        free(tmp);
    }
}


// Algorithme A* pour trouver l'un des chemins les plus courts entre deux sommets
int* a_star(matrice_sup* mat_st, int depart, int arrivee, float distance_max){
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
