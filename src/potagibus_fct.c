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


// Donne le nombre de ligne d'un fichier si son nombre de caractère par ligne est inférieur à 200
int nb_ligne(const char* filename) {
    // Ouverture du fichier
    FILE* file = fopen(filename, "r");
    if (!file) { // Si le fichier n'existe pas
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        return -1;
    }

    // Comptage du nombre de ligne
    int nb_ligne = 0;
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, file)) {
        nb_ligne++;
    }

    // Fermeture du fichier
    fclose(file);
    return nb_ligne;
}

// Lit un fichier csv et renvoie un tableau de station
station_tab* read_csv_station_tab(const char* filename) {
    // Ouverture du fichier
    FILE* file = fopen(filename, "r"); 
    if (!file) { // Si le fichier n'existe pas
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }

    // Buffer de lecture
    char buffer[BUFFER_SIZE];

    // Allocation mémoire de la structure station
    station_tab* tab_s = malloc(sizeof(station_tab));
    if (!tab_s) { // Si l'allocation mémoire a échoué
        printf("Erreur d'allocation mémoire\n");
        return NULL;
    }

    // Initialisation du tableau de station
    tab_s -> taille = nb_ligne(filename) - 1;
    tab_s -> tab = malloc(tab_s -> taille * sizeof(station));
    if (!tab_s -> tab) { // Si l'allocation mémoire a échoué
        printf("Erreur d'allocation mémoire\n");
        return NULL;
    }

    // Lecture du fichier et remplissage du tableau
    int i = -1;
    while (fgets(buffer, BUFFER_SIZE, file)) {
        // On saute la première ligne
        if (i == -1) {
            i++;
            continue;
        }

        // On récupère les informations de la station
        char* id_str = strtok(buffer, ",");
        char* lon_str = strtok(NULL, ",");
        char* lat_str = strtok(NULL, ",");
        char* nb_pdc_str = strtok(NULL, ",");
        char* puis_str = strtok(NULL, ",");
        if (!id_str || !lon_str || !lat_str || !nb_pdc_str || !puis_str) { // Si le format du fichier est incorrect
            printf("Format de fichier incorrect\n");
            return NULL;
        }

        // On rempli la structure station
        strncpy(tab_s -> tab[i].id, id_str, LENGTH_ID - 1);
        tab_s -> tab[i].id[LENGTH_ID - 1] = '\0';
        tab_s -> tab[i].longitude = atof(lon_str);
        tab_s -> tab[i].latitude = atof(lat_str);
        tab_s -> tab[i].nbre_pdc = atoi(nb_pdc_str);
        tab_s -> tab[i].nbre_pdc_dispo = tab_s -> tab[i].nbre_pdc;
        tab_s -> tab[i].puissance = atoi(puis_str);

        // On passe à la station suivante
        i++;
    }

    fclose(file);
    return tab_s;
}

// Détruit un tableau de station
void destroy_station_tab(station_tab* tab_s) {
    free(tab_s -> tab);
    free(tab_s);
}

// Affiche une station du tableau de station | DEBUG
void print_station_tab(station_tab* tab_s, int i) {
    printf("Station %d : %s, %f, %f, %d, %d, %d\n", i, tab_s -> tab[i].id, tab_s -> tab[i].longitude, tab_s -> tab[i].latitude, tab_s -> tab[i].nbre_pdc, tab_s -> tab[i].nbre_pdc_dispo, tab_s -> tab[i].puissance);
}

// Donne la taille du tableau de station
int taille_station_tab(station_tab* tab_s) {
    return tab_s -> taille;
}

// Donne la station d'indice i du tableau de station
station* get_station_tab(station_tab* tab_s, int i) {
    return &tab_s -> tab[i];
}

// Donne la longitude de la station d'indice i du tableau de station
double get_station_tab_longitude(station_tab* tab_s, int i) {
    return tab_s -> tab[i].longitude;
}

// Donne la latitude de la station d'indice i du tableau de station
double get_station_tab_latitude(station_tab* tab_s, int i) {
    return tab_s -> tab[i].latitude;
}

// Donne le nombre de place de la station d'indice i du tableau de station
int get_station_tab_nbre_pdc(station_tab* tab_s, int i) {
    return tab_s -> tab[i].nbre_pdc;
}

// Donne le nombre de place disponible de la station d'indice i du tableau de station
int get_station_tab_nbre_pdc_dispo(station_tab* tab_s, int i) {
    return tab_s -> tab[i].nbre_pdc_dispo;
}

// Donne la puissance de la station d'indice i du tableau de station
int get_station_tab_puissance(station_tab* tab_s, int i) {
    return tab_s -> tab[i].puissance;
}

// Donne l'identifiant de la station d'indice i du tableau de station
char* get_station_tab_id(station_tab* tab_s, int i) {
    return tab_s -> tab[i].id;
}

// Modifie le nombre de place disponible de la station d'indice i du tableau de station
void set_station_tab_nbre_pdc_dispo(station_tab* tab_s, int i, int nbre_pdc_dispo) {
    // On vérifie que le nombre de place disponible est positif
    if (nbre_pdc_dispo < 0) {
        printf("Erreur : le nombre de place disponible ne peut pas être négatif\n");
        return;
    }

    // On vérifie que le nombre de place disponible est inférieur ou égal au nombre de place
    if (nbre_pdc_dispo > tab_s -> tab[i].nbre_pdc) {
        printf("Erreur : le nombre de place disponible ne peut pas être supérieur au nombre de place\n");
        return;
    }

    tab_s -> tab[i].nbre_pdc_dispo = nbre_pdc_dispo;
}

// Lit un fichier csv et renvoie un tableau de voiture
voiture_tab* read_csv_voiture_tab(const char* filename) {
    // Ouverture du fichier
    FILE* file = fopen(filename, "r"); 
    if (!file) { // Si le fichier n'existe pas
        printf("Impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }

    // Buffer de lecture
    char buffer[BUFFER_SIZE];

    // Allocation mémoire de la structure voiture
    voiture_tab* tab_v = malloc(sizeof(voiture_tab));
    if (!tab_v) { // Si l'allocation mémoire a échoué
        printf("Erreur d'allocation mémoire\n");
        return NULL;
    }

    // Initialisation du tableau de voiture
    tab_v -> taille = nb_ligne(filename) - 1;
    tab_v -> tab = malloc(tab_v -> taille * sizeof(voiture));
    if (!tab_v -> tab) { // Si l'allocation mémoire a échoué
        printf("Erreur d'allocation mémoire\n");
        return NULL;
    }

    // Lecture du fichier et remplissage du tableau
    int i = -1;
    while (fgets(buffer, BUFFER_SIZE, file)) {
        // On saute la première ligne
        if (i == -1) {
            i++;
            continue;
        }

        // On récupère les informations de la voiture
        char* name_str = strtok(buffer, ";");
        char* range_str = strtok(NULL, ";");
        char* acc_str = strtok(NULL, ";");
        char* top_str = strtok(NULL, ";");
        char* eff_str = strtok(NULL, ";");
        char* fast_str = strtok(NULL, ";");
        if (!name_str || !range_str || !acc_str || !top_str || !eff_str || !fast_str) { // Si le format du fichier est incorrect
            printf("Format de fichier incorrect\n");
            return NULL;
        }

        // On rempli la structure voiture
        strncpy(tab_v -> tab[i].name, name_str, LENGTH_NAME - 1);
        tab_v -> tab[i].name[LENGTH_NAME - 1] = '\0';
        tab_v -> tab[i].range = atoi(range_str);
        tab_v -> tab[i].efficiency = atoi(eff_str);
        tab_v -> tab[i].fast_charge = atoi(fast_str);

        // On passe à la voiture suivante
        i++;        
    }

    fclose(file);
    return tab_v;
}

// Détruit un tableau de voiture
void destroy_voiture_tab(voiture_tab* tab_v) {
    free(tab_v -> tab);
    free(tab_v);
}

// Affiche une voiture du tableau de voiture | DEBUG
void print_voiture_tab(voiture_tab* tab_v, int i) {
    printf("Voiture %d : %s, %d, %d, %d\n", i, tab_v -> tab[i].name, tab_v -> tab[i].range, tab_v -> tab[i].efficiency, tab_v -> tab[i].fast_charge);
}

// Donne la taille du tableau de voiture
int taille_voiture_tab(voiture_tab* tab_v) {
    return tab_v -> taille;
}

// Donne la voiture d'indice i du tableau de voiture
voiture* get_voiture_tab(voiture_tab* tab_v, int i) {
    return &tab_v -> tab[i];
}

// Donne le nom de la voiture d'indice i du tableau de voiture
char* get_voiture_tab_name(voiture_tab* tab_v, int i) {
    return tab_v -> tab[i].name;
}

// Donne la portée de la voiture d'indice i du tableau de voiture
int get_voiture_tab_range(voiture_tab* tab_v, int i) {
    return tab_v -> tab[i].range;
}

// Donne l'efficacité de la voiture d'indice i du tableau de voiture
int get_voiture_tab_efficiency(voiture_tab* tab_v, int i) {
    return tab_v -> tab[i].efficiency;
}

// Donne la capacité de charge rapide de la voiture d'indice i du tableau de voiture
int get_voiture_tab_fast_charge(voiture_tab* tab_v, int i) {
    return tab_v -> tab[i].fast_charge;
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
