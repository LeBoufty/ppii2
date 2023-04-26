#include "coord.h"

// Création d'un point
coord* create_coord() {
    coord* point = malloc(sizeof(coord));
    return point;
}

// Libère la mémoire d'un point
void destroy_coord(coord* point) {
    free(point);
}

// Donne le x d'un point
double get_coord_x(coord* point) {
    return point -> x;
}

// Set le x d'un point
void set_coord_x(coord* point, double x) {
    point -> x = x;
}

// Donne le y d'un point
double get_coord_y(coord* point) {
    return point -> y;
}

// Set le y d'un point
void set_coord_y(coord* point, double y) {
    point -> y = y;
}

// Donne une distance selon la formule de Haversine entre deux points
float distance(coord* p1, coord* p2) {
    float x1=(p1->x)*DEG_TO_RAD;float y1=(p1->y)*DEG_TO_RAD;
    float x2=(p2->x)*DEG_TO_RAD;float y2=(p2->y)*DEG_TO_RAD;
    if (x1==x2 && y1==y2){return 0;}
    float A= sin(y1)*sin(y2) + cos(y1)*cos(y2)*cos(x2-x1);
    if (A>1){A=1;}
    if (A<-1){A=-1;}
    return 6371*acosf(A);
}

// Donne une distance euclidienne entre deux points
float distance_euclid(coord* p1, coord* p2) {
    return sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
}

// Exclut un point si il est dans un carré avec une marge
bool excl_carre(coord* point, coord* dep, coord* arr, int marge){
    bool res=true;

    if(dep->x>arr->x)
    {
        if(point->x>(dep->x+marge)||point->x<(arr->x-marge))
        {
            res=false;
        }
    }
    else if(point->x>(arr->x+marge)||point->x<(dep->x-marge))
    {
        res=false;
    }

    if(dep->y>arr->y)
    {
        if(point->y>(dep->y+marge)||point->y<(arr->y-marge))
        {
            res=false;
        }
    }
    else if(point->y>(arr->y+marge)||point->y<(dep->y-marge))
    {
        res=false;
    }
    return(res);
}

// Exclut un point si il est dans un ovale avec une marge
bool excl_ovale(coord* point, coord* dep, coord* arr, double marge)
{
    float distab,N,distac,distbc;
    distab=distance(dep,arr);
    distac=distance(dep,point);
    distbc=distance(point,arr);
    N=distab+marge/distab;
    if(distac+distbc<=N)
    {
        return(true);
    }
    else
    {
        return(false);
    }

}
