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

// Destruction d'un chemin et de tous ses éléments | Non utilisé, utilisé destroy_garbage_list
chemin* destroy_chemin(chemin* c){ 
    // Si le chemin n'existe pas, on ne fait rien
    if (c == NULL){ 
        return NULL;
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
garbage_list* create_garbage_list(){ 
    garbage_list* g = malloc(sizeof(garbage_list));
    g -> taille = 0;
    g -> taille_max = INITIAL_SIZE;
    g -> chemin = malloc(sizeof(chemin*) * g -> taille_max);
    return g;
}

// Ajout d'un élément à la liste de garbage
void push_garbage_list(garbage_list* g, chemin* c){ 
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
void destroy_garbage_list(garbage_list* g){ 
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
void enqueue_file(file* f, chemin* c, garbage_list* g, int id, float distance_approche){ 
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

    // Ajout de l'élément à la liste de garbage
    push_garbage_list(g, c);

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
        destroy_chemin(tmp -> chemin); // BUG c'est sûr ! 
        free(tmp);
    }
}