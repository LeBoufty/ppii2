#include "list_int.h"

// Crée une liste d'entiers vide
list_int* create_list_int() {
    list_int* list = malloc(sizeof(list_int));
    list->element = 0;
    list->next = NULL;
    return list;
}

// Destruction d'une liste de int
void destroy_list_int(list_int* one_list){
    list_int* current = one_list;
    while (current != NULL){
        list_int* next = current -> next;
        free(current);
        current = next;
    }
}

// Vérifie si une liste de int est vide
bool is_empty_list_int(list_int* one_list){
    if (one_list == NULL){
        return true;
    }
    if (one_list -> next == NULL){
        return true;
    }
    return false;
}

// Ajout d'un élément au début d'une liste de int
void append_list_int(list_int* one_list, int element){
    list_int* list_suiv = create_list_int();
    list_suiv -> element = one_list -> element;
    list_suiv -> next = one_list -> next;
    one_list -> element = element;
    one_list -> next = list_suiv;
}

// Taille d'une liste de int
int size_list_int(list_int* one_list){
    list_int* list = one_list;
    int size = 0;
    while (list != NULL){
        size += 1;
        list = list -> next;
    }
    return(size - 1);
}

// Suppression du premier élément d'une liste de int
int pop_list_int(list_int* one_list){
    // Si la liste est vide
    if (one_list == NULL){
        printf("ERREUR Liste inexistante\n");
        return -1;
    }
    // Si la liste ne contient qu'un élément
    if (one_list -> next == NULL){
        printf("ERREUR La liste est vide\n");
        return -1;
    }
    // Sinon
    int element_r = one_list -> element;
    list_int* list_suiv = one_list -> next;
    one_list -> element = list_suiv -> element;
    one_list -> next = list_suiv -> next;
    free(list_suiv);
    return element_r;
}
