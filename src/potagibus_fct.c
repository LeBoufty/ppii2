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

bool excl_ovale(coord* point, coord* dep, coord* arr, int marge)
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

float** create_Matrice(int n) /* Créer une matrice triangulaire supérieur(la partie basse de la matrice est tout simplement pas généré) de taille n-1 x n-1 */{
    float** mat=(float**) malloc((n-1)*sizeof(float*));
    for (int i=0; i<n-1; i++) {
        mat[i]=(float*) malloc((i+1)*sizeof(float));
    }
    return mat;
}

float element_mat(float** mat,int x, int y) /*sert à renvoyer l'élément de la martice triangulaire situé à la ligne x et à la colonne y*/
{
    if(y>sizeof(mat[x])) /* décalage d'indice et x=y*/
    {
        return(mat[y][x]);
    }
    else
    {
        return(mat[x][y]);
    }
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


float** suppr_point(coord* depart, coord* arrivee, float** tableau) /*utilise la matrice triangulaire pour éliminer les points inutiles grâce à la méthode des "ovales". Renvoi un tableau formé de tableaux avec un élément de la struct "coord" qui correspondront aux coordonnées x et y dans le tableau triangulaire des points utilisables.*/
{
    int marge=1;
    list_t* liste;
    liste=uppr_point_int(depart, arrivee, tableau, marge);
    while((list_is_empty(liste))||marge>10)
    {
        marge+=1;
        liste=uppr_point_int(depart, arrivee, tableau, marge);        
    }
    if(list_is_empty(liste))
    {
        return(NULL);
    }
    else
    {
        int size=list_size(liste);
        int k;
        float** res=(float**) malloc(size*(sizeof(coord*)));
        list_t* liste_int=liste;
        int size=0;
        for(k=0;k<size;k++)
        {
            res[k]=liste_int->element;
            liste_int=liste_int->next;
        }
        list_destroy(liste);
        return(res);
    }
    
}

list_t* suppr_point_int(coord* depart, coord* arrivee, float** tableau, int marge) /*fonction intermédiaire de suppr_point utilisé pour la récusricitvé*/
{
    list_t* liste=list_create();
    coord* coord_pt;
    int i,j;
    for(i=0;i<sizeof(tableau);i++)
    {
        for(j=0;j<sizeof(tableau[j]);j++)
        {
            coord_pt->x=i;
            coord_pt->y=j;
            if(excl_ovale(coord_pt,depart,arrivee,marge))
            {
                if(liste->next==NULL)
                {
                    liste->element=coord_pt;
                }
                else
                {
                    list_append(liste,i,j);
                }
            }
        }
    }
    return(liste);
}


/*Gen_Matrice(List_points_Trie : list_t*, Taille : Int)->Matrice_Adj : float** */
float** Gen_Matrice(list_t* List_points_Trie, int taille){
    float** mat=create_Matrice(taille);
    list_t* p1=List_points_Trie;
    for (int i=0;i<taille-1; i++){
        list_t* p2=p1->next;
        for (int j=0;j<taille-i-1;j++){ /* Parcous en largeur du tableau sachant qu'on prend pas en compte la distance entre un point et lui même*/
            float a=distance(p1->element,p2->element);
            mat[i][j]=a;
            p2=p2->next;
        }
        p1=p1->next;
    }
    return mat;
}

//fonctions d'actions sur les listes chainées



list_t* list_create(){
    list_t* list=malloc(sizeof(list_t));
    coord* e1=calloc(1,sizeof(coord));
    list->element=e1;
    list->next=NULL;
    return list;
}


void list_destroy(list_t *one_list){
    list_t* point=one_list;list_t* point2=one_list;
    while (point2!=NULL){
        point2=point2->next;
        free(point);
        point=point2;
    }
}

bool list_is_empty(list_t* one_list){
    if (one_list==NULL){return true;}
    return false;
}

void list_append(list_t* one_list, float coord_x, float coord_y){
    list_t* list=list_create();
    list->element=one_list->element;
    list->next=one_list->next;
    one_list->element->x=coord_x;
    one_list->element->y=coord_y;
    one_list->next=list;
}

void element_print(coord* one_element){
    printf("%s: %s",one_element->x,one_element->y);
}

void list_print(list_t* one_list){
    list_t* list=one_list;
    while (list!=NULL){
        element_print(list->element);
        list=list->next;
    }
}

int list_size(list_t* one_list){
    list_t* list=one_list;
    int size=0;
    while (list!=NULL){
        size+=1;
        list=list->next;
    }
    return(size);
}