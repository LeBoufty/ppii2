#include "a_star_struct.h"

// Création d'une liste de garbage vide
garbage_chemin* create_garbage_chemin(){ 
    garbage_chemin* g = malloc(sizeof(garbage_chemin));
    g -> taille = 0;
    g -> taille_max = INITIAL_SIZE_GARBAGE;
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

// Création d'un chemin vide
chemin* create_chemin(garbage_chemin* gc){ 
    chemin* c = malloc(sizeof(chemin));
    c -> id = -1;  
    // Les derniers éléments du chemin sont toujours NULL
    c -> suivant = NULL;
    c -> distance_total = 0;
    c -> distance_prochain = 0;
    c -> capacite_avant = 0;
    c -> capacite_apres = 0;
    
    push_garbage_chemin(gc, c);
    return c;
}

// Ajout d'un élément au chemin en tête de liste
chemin* push_chemin(chemin* c, int id, double distance, double capacite_avant, double capacite_apres, garbage_chemin* gc){ 
    // Si le chemin n'existe pas, on ne fait rien
    if (c == NULL){ 
        return NULL;
    }

    // Création d'un nouvel élément
    chemin* new = create_chemin(gc); 
    new -> id = id;
    new -> suivant = c;
    new -> distance_total = distance + c -> distance_total;
    new -> distance_prochain = distance;
    new -> capacite_avant = capacite_avant;
    new -> capacite_apres = capacite_apres;

    return new;
}

// Taille d'un chemin
int size_chemin(chemin* c){ 
    // Si le chemin n'existe pas, retourne 0
    if (c == NULL){ 
        return 0;
    }

    // Parcours du chemin pour compter le nombre d'éléments
    int taille = -1;
    while (c != NULL){
        taille++;
        c = c -> suivant;
    }
    return taille;
}

// Distance totale d'un chemin depuis le début
double get_chemin_distance_totale(chemin* c){ 
    // Si le chemin n'existe pas, retourne 0
    if (c == NULL){ 
        return 0;
    }

    return c -> distance_total;
}

// Distance du prochain élément du chemin
double get_chemin_distance_prochain(chemin* c){ 
    // Si le chemin n'existe pas, retourne 0
    if (c == NULL){ 
        return 0;
    }

    return c -> distance_prochain;
}

// Capacité avant le prochain élément du chemin
double get_chemin_capacite_avant(chemin* c){ 
    // Si le chemin n'existe pas, retourne 0
    if (c == NULL){ 
        return 0;
    }

    return c -> capacite_avant;
}

// Capacité après le prochain élément du chemin
double get_chemin_capacite_apres(chemin* c){ 
    // Si le chemin n'existe pas, retourne 0
    if (c == NULL){ 
        return 0;
    }

    return c -> capacite_apres;
}

// ID du prochain élément du chemin
int get_chemin_id(chemin* c){ 
    // Si le chemin n'existe pas, retourne -1
    if (c == NULL){ 
        return -1;
    }

    return c -> id;
}

// Copie d'un chemin en un tableau d'entiers géré dynamiquement | Ancien code, non utilisé
int* copy_chemin(chemin* c){
    printf("Ne pas utiliser copy_chemin\n"); 
    // Si le chemin n'existe pas, on ne fait rien
    if (c == NULL){ 
        return NULL;
    }

    // Création d'un tableau dynamique
    int taille = size_chemin(c);
    int* tab = malloc(sizeof(int) * taille);

    // Copie du chemin dans le tableau
    for (int i = 0; i < taille; i++){ 
        tab[i] = c -> id;
        c = c -> suivant;
    }
    return tab;
}

// Destruction d'un chemin et de tous ses éléments | Ne pas utilisé, utiliser destroy_garbage_chemin
void destroy_chemin(chemin* c){
    printf("Ne pas utiliser destroy_chemin\n"); 
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



// Création d'une file de priorité triée par distance
file* create_file(){ 
    file* f = malloc(sizeof(file));
    f -> distance_approche = -1;
    // Les premiers éléments de la file sont toujours NULL
    f -> chemin = NULL; 
    f -> suivant = NULL;
    f -> precedent = NULL;
    return f;
}

// Ajout d'un élément dans la file de priorité triée par distance
void enqueue_file(file* f, chemin* c, double distance_approche){ 
    // Si la file n'existe pas, on ne fait rien
    if (f == NULL){ 
        return;
    }

    // Création d'un nouvel élément
    file* new = create_file(); 
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
chemin* dequeue_file(file* f){
    // Si la file n'existe pas, on ne fait rien
    if (f == NULL){
        return NULL;
    }

    // Si la file est vide, on ne fait rien
    if (f -> suivant == NULL){ 
        return NULL;
    }

    // Récupération des informations du premier élément de la file
    file* tmp = f -> suivant; 
    chemin* c = tmp -> chemin; 

    // Suppression du premier élément de la file
    f -> suivant = tmp -> suivant;
    if (tmp -> suivant != NULL){
        file* tmp_suivant = tmp -> suivant;
        tmp_suivant -> precedent = f;
    }
    free(tmp);

    return c;
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

    
    if (get_chemin_id(f -> suivant -> chemin) == id){
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

// Création du tableau visites
visite_tab* create_visite_tab(int taille){
    visite_tab* v = malloc(sizeof(visite_tab));
    v -> taille = taille;
    v -> tab = malloc(sizeof(int) * taille); // sizeof(bool) ne marche pas
    for (int i = 0; i < taille; i++){
        v -> tab[i] = false;
    }
    return v;
}

// Donne la valeur d'une case du tableau visites
bool get_visite_tab(visite_tab* v, int id){
    // Si le tableau n'existe pas, on retourne false
    if (v == NULL){
        return false;
    }

    // Si l'id est en dehors du tableau, on retourne false
    if (id < 0 || id >= v -> taille){
        return false;
    }

    return v -> tab[id];
}

// Met à jour la valeur d'une case du tableau visites
void set_visite_tab(visite_tab* v, int id, bool value){
    // Si le tableau n'existe pas, on ne fait rien
    if (v == NULL){
        return;
    }

    // Si l'id est en dehors du tableau, on ne fait rien
    if (id < 0 || id >= v -> taille){
        return;
    }

    v -> tab[id] = value;
}

// Destruction du tableau visites
void destroy_visite_tab(visite_tab* v){
    // Si le tableau n'existe pas, on ne fait rien
    if (v == NULL){
        return;
    }

    // Destruction du tableau
    free(v -> tab);
    free(v);
}

// Fonction pour récupérer un élément de la matrice en incluant les coordonnées de début et de fin
double get_element_matrice_struc_a_star(matrice_inf* mat, int i, int j, coord* depart, coord* arrivee, station_tab* tab_s) {
    if (i != -1 && i != -2  && j != -1 && j != -2) {
        return get_element_matrice_struc(mat, i, j);
    }

    // Cas spéciaux
    if (i == j) {
        return 0;
    }
    if ((i == -1 && j == -2) || (i == -2 && j == -1)) {
        return distance(depart, arrivee);
    }
    if (i == -1) {
        return distance(depart, get_station_tab_coord(tab_s, j));
    }
    if (j == -1) {
        return distance(depart, get_station_tab_coord(tab_s, i));
    }
    if (i == -2) {
        return distance(arrivee, get_station_tab_coord(tab_s, j));
    }
    if (j == -2) {
        return distance(arrivee, get_station_tab_coord(tab_s, i));
    }
    return get_element_matrice_struc(mat, i, j);
}
