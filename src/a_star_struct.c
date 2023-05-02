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
    new -> distance_totale = distance + c -> distance_total;
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
double get_distance_totale_chemin(chemin* c){ 
    // Si le chemin n'existe pas, retourne 0
    if (c == NULL){ 
        return 0;
    }

    return c -> distance;
}

// Distance du prochain élément du chemin
double get_distance_prochain_chemin(chemin* c){ 
    // Si le chemin n'existe pas, retourne 0
    if (c == NULL){ 
        return 0;
    }

    return c -> distance_prochain;
}

// Capacité avant le prochain élément du chemin
double get_capacite_avant_chemin(chemin* c){ 
    // Si le chemin n'existe pas, retourne 0
    if (c == NULL){ 
        return 0;
    }

    return c -> capacite_avant;
}

// Capacité après le prochain élément du chemin
double get_capacite_apres_chemin(chemin* c){ 
    // Si le chemin n'existe pas, retourne 0
    if (c == NULL){ 
        return 0;
    }

    return c -> capacite_apres;
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
