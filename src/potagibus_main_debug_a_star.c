#include "potagibus_a_star.h"

int main(int argc, char** argv){
    // Initialisation de la matrice d'adjacence
    argc = 0;
    argv = NULL;

    // Initialisation du chemin
    chemin* c = create_chemin();
    // Ajout d'éléments au chemin
    c = push_chemin(c, 1, 1);
    c = push_chemin(c, 2, 2);
    c = push_chemin(c, 3, 3);
    chemin* a = c;
    // Affichage du chemin
    printf("Chemin : ");
    while (a != NULL){
        printf("%d ", a -> id);
        a = a -> suivant;
    }
    destroy_chemin(c);
    printf("\n");

    // Initialisation de la file
    file* f = create_file();
    // Ajout d'éléments à la file
    enqueue_file(f, c, 1, 1);
    enqueue_file(f, c, 2, 2);
    enqueue_file(f, c, 3, 3);
    // Affichage de la file
    printf("File : ");
    file* b = f -> suivant;
    while (b != NULL){
        printf("%d ", b -> id);
        b = b -> suivant;
    }
    destroy_file(f);
    printf("\n");

    list_t* l = list_create();
    list_append(l, 0, 1);    
    list_append(l, 0, 2);
    list_append(l, 0, 3);
    list_append(l, 0, 4);
    // list_append(l, 1, 2);
    // list_append(l, 2, 3);
    // list_append(l, 3, 4);
    //float** M = create_Matrice(7);
    //set_element_mat(M, 0, 4, 1);
    //set_element_mat(M, 2, 0, 1);
    //float lo = M[0][0];
    //printf("%f\n", lo);
    //float lo = element_mat(M, 1, 0);
    list_print(l);
    list_t* la = list_create();
    printf("%d\n", list_size(la));
    list_destroy(la);

    matrice_inf* M = Gen_Matrice_struc(l);
    // print la matrice
    for (int i = 0; i < M -> taille; i++){
        for (int j = 0; j < M -> taille; j++){
            printf("%f ", element_mat_struc(M, i, j));
        }
        printf("\n");
    }
    int* tab = a_star(M, 0, 3, 1.1);
    printf("%p\n", (void*) tab);
    printf("lol\n");
    for (int i = 0; i < 2; i++){
        printf("%d\n", tab[i]);
    }
    list_destroy(l);
    destroy_Matrice_struc(M);
    free(tab);
    

    return 0;
}
