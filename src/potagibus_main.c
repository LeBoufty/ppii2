#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "potagibus_fct.h"

int main()
{
    //section de tests
    int marge=2;

    coord* a=(coord*)malloc(sizeof(coord));
    coord* b=(coord*)malloc(sizeof(coord));
    coord* c=(coord*)malloc(sizeof(coord));
    coord* d=(coord*)malloc(sizeof(coord));
    coord* e=(coord*)malloc(sizeof(coord));

    a->x=1;
    a->y=1;

    b->x=3;
    b->y=3;

    c->x=2;
    c->y=2;

    d->x=10;
    d->y=9;

    e->x=3;
    e->y=4;

    printf("test pour carré, avec c: %d\n", excl_carre(c, a, b, marge));
    printf("test pour ovale, avec c: %d\n", excl_ovale(c, a, b, marge));
    printf("test pour carré, avec d: %d\n", excl_carre(d, a, b, marge));
    printf("test pour ovale, avec d: %d\n", excl_ovale(d, a, b, marge));
    printf("test pour carré, avec e: %d\n", excl_carre(e, a, b, marge));
    printf("test pour ovale, avec e: %d\n", excl_ovale(e, a, b, marge));

    

    free(a);
    free(b);
    free(c);
    free(d);
    free(e);

    

    struct Station* head = read_csv("../BD/stations.csv");
    if (!head) {
        printf("Erreur lors de la lecture du fichier\n");
        return -1;
    }
    int count = 0;
    for (struct Station* station = head; station; station = station->next) {
        printf("%s,%f,%f,%d\n", station->id, station->longitude, station->latitude, station->nbre_pdc);
        count++;
    }
    printf("Nombre de stations : %d\n", count); 
    // Libérer la mémoire allouée pour chaque station
    for (struct Station* station = head; station; ) {
        struct Station* next = station->next;
        free(station);
        station = next;
    }

}
