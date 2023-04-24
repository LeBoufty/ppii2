#include "list_t.h"

// Création d'une liste vide
list_t* create_list_t() {
    list_t *list = malloc(sizeof(list_t));
    list->element = calloc(1, sizeof(coord));
    list->next = NULL;
    return list;
}

// Destruction d'une liste
void destroy_list_t(list_t *one_list) {
    list_t *current = one_list;
    while (current != NULL) {
        list_t *next = current->next;
        free(current->element);
        free(current);
        current = next;
    }
}

// Vérifie si une liste est vide
bool is_empty_list_t(list_t *one_list) {
    if (one_list == NULL) {
        return true;
    }
    if (one_list->next == NULL) {
        return true;
    }
    return false;
}

// Ajout d'un élément en tête de liste
void append_list_t(list_t *one_list, double x, double y) {
    list_t *list_suiv = create_list_t();
    list_suiv->element->x = one_list->element->x;
    list_suiv->element->y = one_list->element->y;
    list_suiv->next = one_list->next;
    one_list->element->x = x;
    one_list->element->y = y;
    one_list->next = list_suiv;
}

// Print de la liste | DEBUG
void print_list_t(list_t *one_list) {
    list_t *list = one_list;
    while (list != NULL) {
        printf("x:%f y:%f\n", list->element->x, list->element->y);
        list = list->next;
    }
}

// Taille de la liste
int size_list_t(list_t *one_list) {
    list_t *list = one_list;
    int size = 0;
    while (list != NULL) {
        size += 1;
        list = list->next;
    }
    return (size - 1);
}
