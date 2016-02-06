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

/** @brief Initializes the contents of an int_list instance.
 *
 * @param list A pointer to an int_list instance.
 *
 * @return void
 */
void int_list_init(int_list *list);

/** @brief Adds an int_node to the given int_list instance with the given integer value.
 *
 * @param list A pointer to an int_list instance.
 *
 * @param to_add An integer with which to construct an int_node to be added to the list.
 *
 * @return void
 */
void int_list_add(int_list *list, int to_add);

/** @brief Removes a node from the list with the given integer value.
 *
 * @param list A pointer to an int_list instance.
 * 
 * @param to_remove An integer using which an int_node in the int_list may be identified and removed.
 *
 * @return unsigned Returns 1 if an int_node was removed from the list with the given integer value, zero otherwise.
 */
unsigned int_list_remove(int_list *list, int to_remove);

/** @brief Removes all nodes from the list.
 *
 * @param list A pointer to an int_list instance.
 *
 * @return void
 */
void int_list_clear(int_list *list);

#endif //__LIST_H__
