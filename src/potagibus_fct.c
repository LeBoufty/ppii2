#include "potagibus_fct.h"


// Sélectionne les points qui sont dans une zone définie par deux points
station_tab* selec_point_struc(coord* depart, coord* arrivee, station_tab* tab_s)
{
    // Marge de tolérance
    int marge = 1;

    // Création de la liste des points qui sont dans la zone
    list_int* liste_point = selec_point_list(depart, arrivee, tab_s, marge);

    while((liste->element==NULL) && marge<10)
    {
        marge+=1;
        liste=Selection_de_points_int(depart, arrivee, liste_point, marge);
    }
    if(liste==NULL)
    {
        return(NULL);
    }
    else
    {
        return(liste);
    }
    
}


// Renvoie une liste des points qui sont dans une zone définie par deux points
list_t* selec_point_list(coord* depart, coord* arrivee, station_tab* tab_s, int marge) {
    // On crée la liste des points
    list_t* liste = list_create();

    coord* coord_pt;
    while(liste_temp->next!=NULL)
    {
        coord_pt=liste_temp->element;
        if(excl_ovale(coord_pt,depart,arrivee,marge)==1)
        {
            list_append(liste,coord_pt->x,coord_pt->y);
        }
        liste_temp=liste_temp->next;
    }
    coord_pt=liste_temp->element;
    if(excl_ovale(coord_pt,depart,arrivee,marge))
        {
            list_append(liste,coord_pt->x,coord_pt->y);
        }
    if(liste->element==NULL)
    {
        list_destroy(liste);
        return(NULL);
    }
    else
    {
        return(liste);
    }
}






/*Gen_Matrice(List_points_Trie : list_t*, Taille : Int)->Matrice_Adj : float** */
float** Gen_Matrice(list_t* List_points_Trie, int taille){
    float** mat=create_Matrice(taille);
    list_t* p1=List_points_Trie;
    for (int i=0;i<taille-1; i++){
        list_t* p2=p1->next;
        for (int j=0;j<taille-i-1;j++){ /* Parcous en largeur du tableau sachant qu'on prend pas en compte la distance entre un point et lui même*/
            float a=distance(p1->element,p2->element);
            set_element_mat(mat,i,j,a);
            p2=p2->next;
        }
        p1=p1->next;
        
    }
    return mat;
}

// Génère la matrice de distance entre les stations à partir d'une liste de coordonnées
matrice_inf* Gen_Matrice_struc(list_t* List_points_Trie){
    int taille = list_size(List_points_Trie);
    matrice_inf* mat_st = create_Matrice_struc(taille);
    list_t* p1 = List_points_Trie;

    for (int j = 0; j < taille -1 ; j++){
        list_t* p2 = p1 -> next;
        for (int i = j + 1; i < taille; i++){ /* Parcous en largeur du tableau sachant qu'on prend pas en compte la distance entre un point et lui même*/
            float a = distance(p1 -> element, p2 -> element);
            set_element_mat_struc(mat_st, i, j, a);
            p2 = p2 -> next;
        }
        p1 = p1 -> next;
    }
    return mat_st;
}


