#include "matrice.h"

// Création d'une matrice strictement inférieure | Nécessite d'avoir appelé la fonction create_matrice_struc
float** create_matrice(int n) {
    float** mat = (float**) malloc((n - 1) * sizeof(float*));
    for (int i = 0; i < n - 1; i++) {
        mat[i] = (float*) malloc((i + 1) * sizeof(float));
    }
    return mat;
}

// Destruction d'une matrice strictement inférieure | Nécessite d'avoir appelé la fonction destroy_matrice_struc
void destroy_matrice(float** mat, int n) {
    for (int i = 0; i < n - 1; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Création de la structure d'une matrice strictement inférieure
matrice_inf* create_matrice_struc(int n){
    matrice_inf* mat = malloc(sizeof(matrice_inf));
    mat_s -> mat = create_matrice(n);
    mat_s -> taille = n;
    return mat_s;
}

// Récupération d'un élément de la matrice strictement inférieure, 0 si i = j
float get_element_matrice_struc(matrice_inf* mat_s, int i, int j){
    if (i == j){
        return 0;
    }
    if (i > j){
        return mat_s -> mat[i-1][j];
    }
    else{
        return mat_s -> mat[j-1][i];
    }
}

// Modification d'un élément de la matrice strictement inférieure, erreur si i = j
void set_element_matrice_struc(matrice_inf* mat_s, int i, int j, float val){
    if (i == j){
        printf("Erreur : i = j\n");
        return;
    }
    if (i > j){
        mat_s -> mat[i-1][j] = val;
    }
    else{
        mat_s -> mat[j-1][i] = val;
    }
}

// Destruction de la structure d'une matrice strictement inférieure
void destroy_matrice_struc(matrice_inf* mat_s){
    destroy_matrice(mat_s -> mat);
    free(mat_s);
}

// Donne la taille de la matrice strictement inférieure
int size_matrice_struc(matrice_inf* mat_s){
    return mat_s -> taille;
}
