#include "voiture.h"

// Création d'un tableau de voiture
voiture_tab* create_voiture_tab(int taille){
    voiture_tab* v = malloc(sizeof(voiture_tab));
    v -> taille = taille;
    v -> tab = malloc(taille * sizeof(voiture));
    return v;
}

// Destruction d'un tableau de voiture
void destroy_voiture_tab(voiture_tab* v){
    free(v -> tab);
    free(v);
}

// Affichage d'un tableau de voiture | DEBUG
void print_voiture_tab(voiture_tab* v, int i){
    printf("Voiture %d : %s, %d, %d, %d\n", i, v -> tab[i].name, v -> tab[i].range, v -> tab[i].efficiency, v -> tab[i].fast_charge);
}

// Taille d'un tableau de voiture
int size_voiture_tab(voiture_tab* v){
    return v -> taille;
}

// Donne la voiture d'indice i du tableau de voiture
voiture* get_voiture_tab(voiture_tab* v, int i){
    return &v -> tab[i];
}

// Set la voiture d'indice i du tableau de voiture
void set_voiture_tab(voiture_tab* v, int i, voiture* s){
    v -> tab[i] = *s;
}

// Donne le nom de la voiture d'indice i du tableau de voiture
char* get_voiture_tab_name(voiture_tab* v, int i){
    return v -> tab[i].name;
}

// Set le nom de la voiture d'indice i du tableau de voiture
void set_voiture_tab_name(voiture_tab* v, int i, char* name){
    strcpy(v -> tab[i].name, name);
    v -> tab[i].name[LENGTH_NAME - 1] = '\0';
}

// Donne la portée de la voiture d'indice i du tableau de voiture
int get_voiture_tab_range(voiture_tab* v, int i){
    return v -> tab[i].range;
}

// Set la portée de la voiture d'indice i du tableau de voiture
void set_voiture_tab_range(voiture_tab* v, int i, int range){
    v -> tab[i].range = range;
}

// Donne l'efficacité de la voiture d'indice i du tableau de voiture
int get_voiture_tab_efficiency(voiture_tab* v, int i){
    return v -> tab[i].efficiency;
}

// Set l'efficacité de la voiture d'indice i du tableau de voiture
void set_voiture_tab_efficiency(voiture_tab* v, int i, int efficiency){
    v -> tab[i].efficiency = efficiency;
}

// Donne la capacité de charge rapide de la voiture d'indice i du tableau de voiture
int get_voiture_tab_fast_charge(voiture_tab* v, int i){
    return v -> tab[i].fast_charge;
}

// Set la capacité de charge rapide de la voiture d'indice i du tableau de voiture
void set_voiture_tab_fast_charge(voiture_tab* v, int i, int fast_charge){
    v -> tab[i].fast_charge = fast_charge;
}

// Donne la capacité de la voiture d'indice i du tableau de voiture en Wh
int get_voiture_tab_capacity(voiture_tab* v, int i){
    return get_voiture_tab_range(v, i) * get_voiture_tab_efficiency(v, i);
}

// Donne la capacité de charge rapide de la voiture d'indice i du tableau de voiture en W
int get_voiture_tab_fast_charge_W(voiture_tab* v, int i){
    return get_voiture_tab_fast_charge(v, i) * get_voiture_tab_efficiency(v, i);
}

// Donne l'id de la voiture selon son nom
int get_voiture_tab_id(voiture_tab* v, char* name){
    for (int i = 0; i < size_voiture_tab(v); i++){
        if (strcmp(get_voiture_tab_name(v, i), name) == 0){
            return i;
        }
    }
    return -1;
}
