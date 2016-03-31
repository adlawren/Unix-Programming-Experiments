#ifndef __DEQUE_H__
#define __DEQUE_H__

// std
#include "stdio.h"
#include "stdlib.h"

// misc
#include "string.h"
#include "ctype.h"

// local
#include "common.h"

typedef struct dynamic_string_array_t {
  size_t size, max_size, max_string_size;
  char **array;
} dynamic_string_array_t;

/** @brief Initializes the given dynamic string array.
 *
 * @param string_array Pointer to a dynamic string array instance.
 *
 * @param initial_max_size The initially allocated maximum size of the array.
 *
 * @param max_string_size The fixed, allocated maximum number of characters associated with strings in the array.
 *
 * @returns void.
 */
void dynamic_string_array_init(dynamic_string_array_t *string_array, size_t initial_max_size, size_t max_string_size);

/** @brief Adds the given string to the end of the given dynamic string array.
 *
 * @param string_array Pointer to a dynamic string array instance.
 *
 * @param to_add The contents of the string to add.
 *
 * @returns void.
 */
void dynamic_string_array_push(dynamic_string_array_t *string_array, char *to_add);

/** @brief Removes the last string from the given dynamic string array.
 *
 * @param string_array Pointer to a dynamic string array instance.
 *
 * @param result A pointer to contain the contents of the string removed from the array.
 *
 * @returns void.
 */
void dynamic_string_array_pop(dynamic_string_array_t *string_array, char *result);

/** @brief Moves each of the given two strings within the given dynamic string array to the position occupied by the other string.
 *
 * @param string_array Pointer to a dynamic string array instance.
 *
 * @param idx1 The position of the first string.
 *
 * @param idx2 The position of the second string.
 *
 * @returns void.
 */
void dynamic_string_array_swap(dynamic_string_array_t *string_array, int idx1, int idx2);

/** @brief Sorts the contents of the given dynamic string array in alphebetical order.
 *
 * @param string_array Pointer to a dynamic string array instance.
 *
 * @returns void.
 */
void dynamic_string_array_sort(dynamic_string_array_t *string_array);

/** @brief Removes all strings from the given dynamic string array.
 *
 * @param string_array Pointer to a dynamic string array instance.
 *
 * @returns void.
 */
void dynamic_string_array_clear(dynamic_string_array_t *string_array);

#endif //__DEQUE_H__
