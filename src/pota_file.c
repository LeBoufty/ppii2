#include "pota_file.h"

// Donne le nombre de ligne d'un fichier si son nombre de caractère par ligne est inférieur à 200
int nb_ligne(const char* filename) {
    // Ouverture du fichier
    FILE* file = fopen(filename, "r");
    if (!file) { // Si le fichier n'existe pas
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        return -1;
    }

    // Comptage du nombre de ligne
    int nb_ligne = 0;
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file)) {
        nb_ligne++;
    }

    // Fermeture du fichier
    fclose(file);
    return nb_ligne;
}

// Lit un fichier csv et renvoie un tableau de station
station_tab* read_csv_station_tab(const char* filename) {
    // Ouverture du fichier
    FILE* file = fopen(filename, "r"); 
    if (!file) { // Si le fichier n'existe pas
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }

    // Buffer de lecture
    char buffer[BUFFER_SIZE];

    // Création du tableau de station
    int taille = nb_ligne(filename) - 1;
    station_tab* tab_s = create_station_tab(taille);

    // Lecture du fichier et remplissage du tableau
    int i = -1;
    while (fgets(buffer, BUFFER_SIZE, file)) {
        // On saute la première ligne
        if (i == -1) {
            i++;
            continue;
        }

        // On récupère les informations de la station
        char* id_str = strtok(buffer, ",");
        char* lon_str = strtok(NULL, ",");
        char* lat_str = strtok(NULL, ",");
        char* nb_pdc_str = strtok(NULL, ",");
        char* puis_str = strtok(NULL, ",");
        if (!id_str || !lon_str || !lat_str || !nb_pdc_str || !puis_str) { // Si le format du fichier est incorrect
            printf("Format de fichier incorrect\n");
            return NULL;
        }

        // On rempli la structure station
        set_station_tab_id(tab_s, i, id_str);
        set_station_tab_longitude(tab_s, i, atof(lon_str));
        set_station_tab_latitude(tab_s, i, atof(lat_str));
        set_station_tab_nbre_pdc(tab_s, i, atoi(nb_pdc_str));
        set_station_tab_nbre_pdc_dispo(tab_s, i, atoi(nb_pdc_str));
        set_station_tab_puissance(tab_s, i, atoi(puis_str));

        // On passe à la station suivante
        i++;
    }

    fclose(file);
    return tab_s;
}


// Lit un fichier csv et renvoie un tableau de voiture
voiture_tab* read_csv_voiture_tab(const char* filename) {
    // Ouverture du fichier
    FILE* file = fopen(filename, "r"); 
    if (!file) { // Si le fichier n'existe pas
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }

    // Buffer de lecture
    char buffer[BUFFER_SIZE];

    // Création du tableau de voiture
    int taille = nb_ligne(filename) - 1;
    voiture_tab* tab_v = create_voiture_tab(taille);

    // Lecture du fichier et remplissage du tableau
    int i = -1;
    while (fgets(buffer, BUFFER_SIZE, file)) {
        // On saute la première ligne
        if (i == -1) {
            i++;
            continue;
        }

        // On récupère les informations de la voiture
        char* name_str = strtok(buffer, ";");
        char* range_str = strtok(NULL, ";");
        char* acc_str = strtok(NULL, ";");
        char* top_str = strtok(NULL, ";");
        char* eff_str = strtok(NULL, ";");
        char* fast_str = strtok(NULL, ";");
        if (!name_str || !range_str || !acc_str || !top_str || !eff_str || !fast_str) { // Si le format du fichier est incorrect
            printf("Format de fichier incorrect\n");
            return NULL;
        }

        // On rempli la structure voiture
        set_voiture_tab_name(tab_v, i, name_str);
        set_voiture_tab_range(tab_v, i, atof(range_str));
        set_voiture_tab_efficiency(tab_v, i, atof(eff_str));
        set_voiture_tab_fast_charge(tab_v, i, atoi(fast_str));

        // On passe à la voiture suivante
        i++;        
    }

    fclose(file);
    return tab_v;
}
