#include "station.h"

// Crée un tableau de station
station_tab* create_station_tab(int taille) {
    station_tab* tab_s = malloc(sizeof(station_tab));
    tab_s -> taille = taille;
    tab_s -> tab = malloc(taille * sizeof(station));
    for (int i = 0; i < taille; i++) {
        tab_s -> tab[i].coord = create_coord();
    } 
    return tab_s;
}

// Détruit un tableau de station
void destroy_station_tab(station_tab* tab_s) {
    for (int i = 0; i < tab_s -> taille; i++) {
        destroy_coord(tab_s -> tab[i].coord);
    }
    free(tab_s -> tab);
    free(tab_s);
}

// Affiche une station du tableau de station | DEBUG
void print_station_tab(station_tab* tab_s, int i) {
    printf("Station %d : %s, %f, %f, %d, %d, %d\n", i, get_station_tab_id(tab_s, i), get_station_tab_coord_x(tab_s, i), get_station_tab_coord_y(tab_s, i), get_station_tab_nbre_pdc(tab_s, i), get_station_tab_nbre_pdc_dispo(tab_s, i), get_station_tab_puissance(tab_s, i));
}

// Donne la taille du tableau de station
int size_station_tab(station_tab* tab_s) {
    return tab_s -> taille;
}

// Donne la station d'indice i du tableau de station
station* get_station_tab(station_tab* tab_s, int i) {
    return &tab_s -> tab[i];
}

// Set la station d'indice i du tableau de station
void set_station_tab(station_tab* tab_s, int i, station* s) {
    tab_s -> tab[i] = *s;
}

// Donne l'identifiant de la station d'indice i du tableau de station
char* get_station_tab_id(station_tab* tab_s, int i) {
    return tab_s -> tab[i].id;
}

// Set l'identifiant de la station d'indice i du tableau de station
void set_station_tab_id(station_tab* tab_s, int i, char* id) {
    strcpy(tab_s -> tab[i].id, id);
    tab_s -> tab[i].id[LENGTH_ID - 1] = '\0';
}

// Donne les coordonnées de la station d'indice i du tableau de station
coord* get_station_tab_coord(station_tab* tab_s, int i) {
    return tab_s -> tab[i].coord;
}

// Donne la coordonnée x de la station d'indice i du tableau de station
double get_station_tab_coord_x(station_tab* tab_s, int i) {
    return get_coord_x(tab_s -> tab[i].coord);
}

// Donne la coordonnée y de la station d'indice i du tableau de station
double get_station_tab_coord_y(station_tab* tab_s, int i) {
    return get_coord_y(tab_s -> tab[i].coord);
}

// Set la coordonnée x de la station d'indice i du tableau de station
void set_station_tab_coord_x(station_tab* tab_s, int i, double x) {
    set_coord_x(tab_s -> tab[i].coord, x);
}

// Set la coordonnée y de la station d'indice i du tableau de station
void set_station_tab_coord_y(station_tab* tab_s, int i, double y) {
    set_coord_y(tab_s -> tab[i].coord, y);
}

// Donne le nombre de pdc de la station d'indice i du tableau de station
int get_station_tab_nbre_pdc(station_tab* tab_s, int i) {
    return tab_s -> tab[i].nbre_pdc;
}

// Set le nombre de pdc de la station d'indice i du tableau de station
void set_station_tab_nbre_pdc(station_tab* tab_s, int i, int nbre_pdc) {
    tab_s -> tab[i].nbre_pdc = nbre_pdc;
}

// Donne le nombre de pdc dispo de la station d'indice i du tableau de station
int get_station_tab_nbre_pdc_dispo(station_tab* tab_s, int i) {
    return tab_s -> tab[i].nbre_pdc_dispo;
}

// Set le nombre de pdc dispo de la station d'indice i du tableau de station
void set_station_tab_nbre_pdc_dispo(station_tab* tab_s, int i, int nbre_pdc_dispo) {
    // On vérifie que le nombre de place disponible est positif
    if (nbre_pdc_dispo < 0) {
        printf("Erreur : le nombre de place disponible ne peut pas être négatif\n");
        return;
    }

    // On vérifie que le nombre de place disponible est inférieur ou égal au nombre de place
    if (nbre_pdc_dispo > get_station_tab_nbre_pdc(tab_s, i)) {
        printf("Erreur : le nombre de place disponible ne peut pas être supérieur au nombre de place\n");
        return;
    }

    tab_s -> tab[i].nbre_pdc_dispo = nbre_pdc_dispo;
}

// Add une valeur au nombre de pdc dispo de la station d'indice i du tableau de station
void add_station_tab_nbre_pdc_dispo(station_tab* tab_s, int i, int valeur_nbre_pdc_dispo) {
    // On vérifie que le nombre de place disponible est positif
    if (valeur_nbre_pdc_dispo + get_station_tab_nbre_pdc_dispo(tab_s, i) < 0) {
        printf("Erreur : le nombre de place disponible ne peut pas être négatif\n");
        return;
    }

    // On vérifie que le nombre de place disponible est inférieur ou égal au nombre de place
    if (tab_s -> tab[i].nbre_pdc_dispo + valeur_nbre_pdc_dispo > tab_s -> tab[i].nbre_pdc) {
        printf("Erreur : le nombre de place disponible ne peut pas être supérieur au nombre de place\n");
        return;
    }

    tab_s -> tab[i].nbre_pdc_dispo += valeur_nbre_pdc_dispo;
}

// Donne la puissance de la station d'indice i du tableau de station
int get_station_tab_puissance(station_tab* tab_s, int i) {
    return tab_s -> tab[i].puissance;
}

// Set la puissance de la station d'indice i du tableau de station
void set_station_tab_puissance(station_tab* tab_s, int i, int puissance) {
    tab_s -> tab[i].puissance = puissance;
}


// Crée un tableau de correspondance entre les identifiants et les indices des stations
corresp_station_tab* create_corresp_tab(int taille) {
    corresp_station_tab* tab_c = malloc(sizeof(corresp_station_tab));
    tab_c -> taille = taille;
    tab_c -> tab_id = malloc(taille * sizeof(int)); 
    return tab_c;
}

// Détruit un tableau de correspondance entre les identifiants et les indices des stations
void destroy_corresp_tab(corresp_station_tab* tab_c) {
    free(tab_c -> tab_id);
    free(tab_c);
}

// Donne la taille du tableau de correspondance entre les identifiants et les indices des stations
int size_corresp_tab(corresp_station_tab* tab_c) {
    return tab_c -> taille;
}

// Donne l'identifiant de la correspondance d'indice i du tableau de correspondance entre les identifiants et les indices des stations
int get_corresp_tab_id(corresp_station_tab* tab_c, int i) {
    return tab_c -> tab_id[i];
}

// Set l'identifiant de la correspondance d'indice i du tableau de correspondance entre les identifiants et les indices des stations
void set_corresp_tab_id(corresp_station_tab* tab_c, int i, int id) {
    tab_c -> tab_id[i] = id;
}
