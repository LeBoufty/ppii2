#include "chemin.h"

// Création d'un chemin_tab_struct
chemin_tab_struct* create_chemin_tab_struct(int taille, station_tab* tab_s, voiture_tab* tab_v, int id_v){
    chemin_tab_struct* cts = malloc(sizeof(chemin_tab_struct));
    cts -> tab = malloc(sizeof(chemin_tab*) * taille);
    cts -> taille = taille;
    cts -> s_tab = tab_s;
    cts -> v_tab = tab_v;
    cts -> id_v = id_v;
    return cts;
}

// Destruction d'un chemin_tab_struct
void destroy_chemin_tab_struct(chemin_tab_struct* cts){
    free(cts -> tab);
    free(cts);
}

// Get la taille du chemin_tab_struct
int size_chemin_tab_struct(chemin_tab_struct* cts){
    return cts -> taille;
}

// Donne le temps de recharge de la station à l'indice i
double get_chemin_tab_struct_temps_recharge(chemin_tab_struct* cts, int i){
    return (double)(get_chemin_tab_struct_capacite_apres(cts, i) - get_chemin_tab_struct_capacite_avant(cts, i)) / (double)get_voiture_tab_fast_charge_W(cts -> v_tab, get_chemin_tab_struct_id(cts, i));
}

// Donne le temps de trajet (en h) entre la station à l'indice i et la station à l'indice i + 1
double get_chemin_tab_struct_temps_prochain(chemin_tab_struct* cts, int i, int vitesse){
    return get_chemin_tab_struct_distance_prochain(cts, i) / (double)vitesse;
}

// Set l'id de la station à l'indice i
void set_chemin_tab_struct_id(chemin_tab_struct* cts, int i, int id){
    cts -> tab[i].id = id;
}

// Get l'id de la station à l'indice i
int get_chemin_tab_struct_id(chemin_tab_struct* cts, int i){
    return cts -> tab[i].id;
}

// Set la distance à la prochaine station à l'indice i
void set_chemin_tab_struct_distance_prochain(chemin_tab_struct* cts, int i, double distance_prochain){
    cts -> tab[i].distance_prochain = distance_prochain;
}

// Get la distance à la prochaine station à l'indice i
double get_chemin_tab_struct_distance_prochain(chemin_tab_struct* cts, int i){
    return cts -> tab[i].distance_prochain;
}

// Set la capacité de la voiture avant la station à l'indice i
void set_chemin_tab_struct_capacite_avant(chemin_tab_struct* cts, int i, double capacite_avant){
    cts -> tab[i].capacite_avant = capacite_avant;
}

// Get la capacité de la voiture avant la station à l'indice i
double get_chemin_tab_struct_capacite_avant(chemin_tab_struct* cts, int i){
    return cts -> tab[i].capacite_avant;
}

// Set la capacité de la voiture après la station à l'indice i
void set_chemin_tab_struct_capacite_apres(chemin_tab_struct* cts, int i, double capacite_apres){
    cts -> tab[i].capacite_apres = capacite_apres;
}

// Get la capacité de la voiture après la station à l'indice i
double get_chemin_tab_struct_capacite_apres(chemin_tab_struct* cts, int i){
    return cts -> tab[i].capacite_apres;
}

