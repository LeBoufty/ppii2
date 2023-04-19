#include "potagibus_fct.h"

 
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

struct Station* read_csv(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }
    char buffer[128];
    struct Station* head = NULL;
    struct Station* tail = NULL;
    while (fgets(buffer, 128, file)) {
        struct Station* station = malloc(sizeof(struct Station));
        if (!station) {
            printf("Erreur d'allocation mémoire\n");
            return NULL;
        }
        char* id_str = strtok(buffer, ",");
        char* lon_str = strtok(NULL, ",");
        char* lat_str = strtok(NULL, ",");
        char* nbre_str = strtok(NULL, ",");
        if (!id_str || !lon_str || !lat_str || !nbre_str) {
            printf("Format de fichier incorrect\n");
            return NULL;
        }
        strncpy(station->id, id_str, 31);
        station->id[31] = '\0';
        station->longitude = atof(lon_str);
        station->latitude = atof(lat_str);
        station->nbre_pdc = atoi(nbre_str);
        station->next = NULL;
        if (!head) {
            head = station;
        } else {
            tail->next = station;
        }
        tail = station;
    }
    fclose(file);
    return head;
}


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

// Donne la distance entre deux stations en fonction de leur id (dans la matrice)
float element_mat(float** mat, int i, int j){
    if (i == j){
        return 0;
    }
    if (i > j){
        return mat[i-1][j];
    }
    else{
        return mat[j-1][i];
    }
}

// Enregistre la distance entre deux stations dans la matrice
void set_element_mat(float** mat, int i, int j, float val){
    if (i == j){
        return;
    }
    if (i > j){
        mat[i-1][j] = val;
    }
    else{
        mat[j-1][i] = val;
    }
}

// Détruit la matrice
void destroy_Matrice(float** mat, int n){
    for (int i=0; i<n-1; i++) {
        free(mat[i]);
    }
    free(mat);
}

// Génération d'une matrice triangulaire supérieur avec sa taille incluse
matrice_inf* create_Matrice_struc(int n){
    matrice_inf* mat_st = (matrice_inf*) malloc(sizeof(matrice_inf));
    mat_st -> taille = n;
    mat_st -> mat = create_Matrice(n);
    return mat_st;
}

// Donne la distance entre deux stations en fonction de leur id (dans la matrice)
float element_mat_struc(matrice_inf* mat_st, int i, int j){
    return element_mat(mat_st->mat, i, j);
}

// Enregistre la distance entre deux stations dans la matrice
void set_element_mat_struc(matrice_inf* mat_st, int i, int j, float val){
    set_element_mat(mat_st->mat, i, j, val);
}

// Donne la taille de la matrice
int taille_mat_struc(matrice_inf* mat_st){
    return mat_st->taille;
}

// Détruit la matrice
void destroy_Matrice_struc(matrice_inf* mat_st){
    destroy_Matrice(mat_st->mat, mat_st->taille);
    free(mat_st);
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

// Donne une distance euclidienne entre deux points
float distance_euclid(coord* p1, coord* p2){
    return sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
}


list_t* Selection_de_points(coord* depart, coord* arrivee, list_t* liste_point)
{
    int marge=1;
    list_t* liste;
    liste=Selection_de_points_int(depart, arrivee, liste_point, marge);
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

list_t* Selection_de_points_int(coord* depart, coord* arrivee, list_t* liste_point, int marge)
{
    list_t* liste=list_create();
    list_t* liste_temp=liste_point;

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

//fonctions d'actions sur les listes chainées



list_t* list_create(){
    list_t* list=malloc(sizeof(list_t));
    list->element=calloc(1,sizeof(coord));
    list->next=NULL;
    return list;
}


void list_destroy(list_t* one_list){
    list_t* current=one_list;
    while (current != NULL){
        list_t* next= current->next;
        free(current->element);
        free(current);
        current=next;
    }
}

bool list_is_empty(list_t* one_list){
    if (one_list==NULL){return true;}
    return false;
}

void list_append_mauvais(list_t* one_list, float coord_x, float coord_y){
    list_t* list=list_create();
    list->element=one_list->element;
    list->next=one_list->next;
    one_list->element->x=coord_x;
    one_list->element->y=coord_y;
    one_list->next=list;
}

void list_append(list_t* one_list, float coord_x, float coord_y){
    list_t* list_suiv = list_create();
    list_suiv -> element -> x = one_list -> element -> x;
    list_suiv -> element -> y = one_list -> element -> y;
    list_suiv -> next = one_list -> next;
    one_list -> element -> x = coord_x;
    one_list -> element -> y = coord_y;
    one_list -> next = list_suiv;
}

void element_print(coord* one_element){
    printf("x:%f y:%f\n",one_element->x,one_element->y);
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
    return(size-1);
}
