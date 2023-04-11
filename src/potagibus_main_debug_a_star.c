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
    list_append(l, 1, 1);
    // printf("%p\n",(void*) l);
    // printf("%p\n",(void*) l->next);
    // printf("%p\n",(void*) l->element);
    // printf("%p\n",(void*) l->next->element);
    
    list_append(l, 2, 2);
    list_append(l, 3, 3);
    list_append(l, 4, 4);
    list_append(l, 1, 2);
    list_append(l, 2, 3);
    list_append(l, 3, 4);
    float** M = Gen_Matrice(l, 7);
    //int* tab = a_star(M, 0, 3, 1);
    printf("lol\n");
    list_destroy(l);
    destroy_Matrice(M, 7);
    //free(tab);

    return 0;
}
