#ifndef _LIST_T_H_
#define _LIST_T_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "coord.h"

struct list_t
{
    coord *element;
    struct list_t *next;
} typedef list_t;

list_t* create_list_t();
void destroy_list_t(list_t* list);
bool is_empty_list_t(list_t* one_list);
void append_list_t(list_t* list, double x, double y);
void print_list_t(list_t* one_list);
int size_list_t(list_t* one_list);


#endif
