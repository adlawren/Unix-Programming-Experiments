#ifndef __LIST_H__
#define __LIST_H__

/*
  Implementation of a linked list in C, wherein nodes contain a single integer for data.
 */

// std
#include "stdlib.h"

typedef struct int_node {
  struct int_node *next;
  int data;
} int_node;


typedef struct int_list {
  int_node *head, *tail;
  unsigned size;
} int_list;

// TODO: add description
void int_list_init(int_list *list);

// TODO: add description
void int_list_add(int_list *list, int to_add);

// TODO: add description
unsigned int_list_remove(int_list *list, int to_remove);

// TODO: add description
void int_list_clear(int_list *list);

#endif //__LIST_H__
