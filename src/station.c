#include "station.h"

// Crée un tableau de station
station_tab* create_station_tab(int taille) {
    station_tab* tab_s = malloc(sizeof(station_tab));
    tab_s -> taille = taille;
    tab_s -> tab = malloc(taille * sizeof(station));
    return tab_s;
}

// Détruit un tableau de station
void destroy_station_tab(station_tab* tab_s) {
    free(tab_s -> tab);
    free(tab_s);
}

// Affiche une station du tableau de station | DEBUG
void print_station_tab(station_tab* tab_s, int i) {
    printf("Station %d : %s, %f, %f, %d, %d, %d\n", i, tab_s -> tab[i].id, tab_s -> tab[i].longitude, tab_s -> tab[i].latitude, tab_s -> tab[i].nbre_pdc, tab_s -> tab[i].nbre_pdc_dispo, tab_s -> tab[i].puissance);
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

// Donne la longitude de la station d'indice i du tableau de station
double get_station_tab_longitude(station_tab* tab_s, int i) {
    return tab_s -> tab[i].longitude;
}

// Set la longitude de la station d'indice i du tableau de station
void set_station_tab_longitude(station_tab* tab_s, int i, double longitude) {
    tab_s -> tab[i].longitude = longitude;
}

// Donne la latitude de la station d'indice i du tableau de station
double get_station_tab_latitude(station_tab* tab_s, int i) {
    return tab_s -> tab[i].latitude;
}

// Set la latitude de la station d'indice i du tableau de station
void set_station_tab_latitude(station_tab* tab_s, int i, double latitude) {
    tab_s -> tab[i].latitude = latitude;
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
    if (nbre_pdc_dispo > tab_s -> tab[i].nbre_pdc) {
        printf("Erreur : le nombre de place disponible ne peut pas être supérieur au nombre de place\n");
        return;
    }

    tab_s -> tab[i].nbre_pdc_dispo = nbre_pdc_dispo;
}

// Donne la puissance de la station d'indice i du tableau de station
int get_station_tab_puissance(station_tab* tab_s, int i) {
    return tab_s -> tab[i].puissance;
}

// Set la puissance de la station d'indice i du tableau de station
void set_station_tab_puissance(station_tab* tab_s, int i, int puissance) {
    tab_s -> tab[i].puissance = puissance;
}
