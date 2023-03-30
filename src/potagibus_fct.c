#include"potagibus.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<math.h>

// float x,y,ax,ay,bx,by; //correspondra aux coordonnées en x et en y respectivement du points dont on veut savoir si on l'utilise, du point de départ et du point d'arrivée

// float marge;

// bool excl_carre(float x,float y,float ax,float ay,float bx,float by,float marge)
// {
//     bool res=true;

//     if(ax>bx)
//     {
//         if(x>(ax+marge)||x<(bx-marge))
//         {
//             res=false;
//         }
//     }
//     else if(x>(bx+marge)||x<(ax-marge))
//     {
//         res=false;
//     }

//     if(ay>by)
//     {
//         if(y>(ay+marge)||y<(by-marge))
//         {
//             res=false;
//         }
//     }
//     else if(y>(by+marge)||y<(ay-marge))
//     {
//         res=false;
//     }
//     return(res);
// }

bool excl_carre(coord* point, coord* dep, coord* arr, int marge)
{
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

bool excl_ovale(coord* point, coord* dep, coord* arr)
{
    float distab,N,distac,distbc;
    distab=sqrt(pow((arr->x-dep->x),2)+pow((arr->y-dep->y),2));
    distac=sqrt(pow((point->x-dep->x),2)+pow((point->y-dep->y),2));
    distbc=sqrt(pow((arr->x-point->x),2)+pow((arr->y-point->y),2));
    N=distab+1/distab;
    if(distac+distbc<=N)
    {
        return(true);
    }
    else
    {
        return(false);
    }

}

int** create_Matrice(int n) /* Créer une matrice triangulaire supérieur(la partie basse de la matrice est tout simplement pas généré) de taille nxn*/{
    int** mat=(int**) malloc(n*sizeof(int*));
    for (int i=0; i<n; i++) {
        mat[i]=(int*) malloc((i+1)*sizeof(int));
    }
    return mat;
}


float distance(coord* p1, coord* p2)/* Calcul de distance cf outils.py */{
    float x1=(p1->x)*0.0174532925;float y1=(p1->y)*0.0174532925;
    float x2=(p2->x)*0.0174532925;float y2=(p2->y)*0.0174532925;
    if (x1==x2 && y1==y2){return 0;}
    float A= sin(y1)*sin(y2) + cos(y1)*cos(y2)*cos(x2-x1);
    if (A>1){A=1;}
    if (A<-1){A=-1;}
    return 6371*acosf(A);
}
