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
}
