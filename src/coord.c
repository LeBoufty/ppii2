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

// Set les coordonnées d'un point
void set_coord(coord* point, double x, double y) {
    set_coord_y(point, x);
    set_coord_x(point, y);
}

// Donne une distance selon la formule de Haversine entre deux points
double distance(coord* p1, coord* p2) {
    double lon1 = get_coord_x(p1)*DEG_TO_RAD;
    double lat1 = get_coord_y(p1)*DEG_TO_RAD;
    double lon2 = get_coord_x(p2)*DEG_TO_RAD;
    double lat2 = get_coord_y(p2)*DEG_TO_RAD;

    double dlon = lon2 - lon1;
    double dlat = lat2 - lat1;

    double a = pow(sin(dlat/2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon/2), 2);
    double c = 2 * asin(sqrt(a));

    return EARTH_RADIUS * c; 
}

// Donne une distance selon la formule de Haversine entre deux points
double distance_anc(coord* p1, coord* p2) {
    double x1 = get_coord_x(p1)*DEG_TO_RAD;
    double y1 = get_coord_y(p1)*DEG_TO_RAD;
    double x2 = get_coord_x(p2)*DEG_TO_RAD;
    double y2 = get_coord_y(p2)*DEG_TO_RAD;
    
    if (x1==x2 && y1==y2){return 0;}
    double A= sin(y1)*sin(y2) + cos(y1)*cos(y2)*cos(x2-x1);
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
    double distab,N,distac,distbc;
    distab=distance(dep,arr);
    distac=distance(dep,point);
    distbc=distance(point,arr);
    N=distab+distab/marge;
    if(distac+distbc<=N)
    {
        return(true);
    }
    else
    {
        return(false);
    }

}
