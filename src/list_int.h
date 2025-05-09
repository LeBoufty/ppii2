#ifndef _LIST_INT_H_
#define _LIST_INT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list_int
{
    int element;
    struct list_int *next;
} list_int;

list_int* create_list_int();
void destroy_list_int(list_int* one_list);
bool is_empty_list_int(list_int* one_list);
void append_list_int(list_int* one_list, int element);
int size_list_int(list_int* one_list);
int pop_list_int(list_int* one_list);

#endif
