#ifndef __POTAGIBUS_H__
#define __POTAGIBUS_H__
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#define LENGTH_ID 40
#define LENGTH_NAME 40
#define BUFFER_SIZE 200
 

struct station {
    char id[LENGTH_ID];
    double longitude;
    double latitude;
    int nbre_pdc;
    int nbre_pdc_dispo;
    int puissance;
} typedef station;

struct station_tab
{
    int taille;
    station* tab;
} typedef station_tab;

struct voiture {
    char name[LENGTH_NAME];
    int range; // en km
    int efficiency; // en Wh/km
    int fast_charge; // en km/h
} typedef voiture;

struct voiture_tab
{
    int taille;
    voiture* tab;
} typedef voiture_tab;

struct _coord
{
    float x;
    float y;
};

struct matrice_inf
{
    int taille;
    float** mat;
} typedef matrice_inf;

typedef struct _coord coord;

struct _list_t { coord* element;struct _list_t* next;};

typedef struct _list_t list_t;

struct _utilisateurs
{
    char voiture;
    float lodepart; //lo=longitude, la=latitude
    float ladepart;
    float loarrivee;
    float laarrivee;
    utilisateurs* next;
};





typedef struct _utilisateurs utilisateurs;

int nb_ligne(const char* filename);

utilisateurs* utilisateurs_create();

utilisateurs* utilisateurs_rdm(voiture_tab* list_v, station_tab* list_s,int n);

station_tab* read_csv_station_tab(const char* filename);

void destroy_station_tab(station_tab* tab_station);

void print_station_tab(station_tab* tab_station, int i);

int taille_station_tab(station_tab* tab_s);

station* get_station_tab(station_tab* tab_s, int i);

double get_station_tab_longitude(station_tab* tab_s, int i);

double get_station_tab_latitude(station_tab* tab_s, int i);

int get_station_tab_nbre_pdc(station_tab* tab_s, int i);

int get_station_tab_nbre_pdc_dispo(station_tab* tab_s, int i);

int get_station_tab_puissance(station_tab* tab_s, int i);

char* get_station_tab_id(station_tab* tab_s, int i);

void set_station_tab_nbre_pdc_dispo(station_tab* tab_s, int i, int nbre_pdc_dispo);

voiture_tab* read_csv_voiture_tab(const char* filename);

void destroy_voiture_tab(voiture_tab* tab_voiture);

void print_voiture_tab(voiture_tab* tab_voiture, int i);

int taille_voiture_tab(voiture_tab* tab_v);

voiture* get_voiture_tab(voiture_tab* tab_v, int i);

char* get_voiture_tab_name(voiture_tab* tab_v, int i);

int get_voiture_tab_range(voiture_tab* tab_v, int i);

int get_voiture_tab_efficiency(voiture_tab* tab_v, int i);

int get_voiture_tab_fast_charge(voiture_tab* tab_v, int i);

float** create_Matrice(int n);

float element_mat(float** mat,int x, int y);

void set_element_mat(float** mat, int x, int y, float val);

void destroy_Matrice(float** mat, int n);

matrice_inf* create_Matrice_struc(int n);

float element_mat_struc(matrice_inf* mat_st, int i, int j);

int taille_mat_struc(matrice_inf* mat_st);

void set_element_mat_struc(matrice_inf* mat_st, int i, int j, float val);

void destroy_Matrice_struc(matrice_inf* mat_st);

float distance(coord* p1, coord* p2);

list_t* Selection_de_points(coord* depart, coord* arrivee, list_t* liste_point);

list_t* Selection_de_points_int(coord* depart, coord* arrivee, list_t* liste_point, int marge);

float** Gen_Matrice(list_t* List_points_Trie, int taille);

matrice_inf* Gen_Matrice_struc(list_t* List_points_Trie);

list_t *list_create();

void list_destroy(list_t *one_list);

bool list_is_empty(list_t *one_list);

void list_append(list_t* one_list, float coord_x, float coord_y);

void element_print(coord *one_element);

void list_print(list_t *one_list);

int list_size(list_t* one_list);

bool excl_carre(coord* point, coord* dep, coord* arr, int marge); 

bool excl_ovale(coord* point, coord* dep, coord* arr, int marge);

#endif
