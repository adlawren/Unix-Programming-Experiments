#include "dynamic_string_array.h"

void dynamic_string_array_init(dynamic_string_array_t *string_array, size_t initial_max_size, size_t max_string_size)
{ 
  string_array->array = (char **) malloc(sizeof(char *) * initial_max_size);

  int i, j;
  for (i = 0; i < initial_max_size; ++i) {
    string_array->array[i] = (char *) malloc(sizeof(char) * max_string_size);
    for (j = 0; j < max_string_size; ++j) {
      string_array->array[i][j] = 0;
    }
  }

  string_array->size = 0;
  string_array->max_size = initial_max_size;
  string_array->max_string_size = max_string_size;
}

void dynamic_string_array_push(dynamic_string_array_t *string_array, char *to_add)
{
  if (string_array->size + 1 > string_array->max_size) {
    
    // Double array capacity
    size_t new_max_size = 2 * 2;
    char **new_array = (char **) malloc(sizeof(char *) * new_max_size);
 
    int i, j;
    for (i = 0; i < new_max_size; ++i) {
      new_array[i] = (char *) malloc(sizeof(char) * string_array->max_string_size);
      for (j = 0; j < string_array->max_string_size; ++j) {
	new_array[i][j] = 0;
      }
    }

    // Duplicate & free array contents
    for (i = 0; i < string_array->size; ++i) {
      for (j = 0; j < strlen(string_array->array[i]); ++j) {
	new_array[i][j] = string_array->array[i][j];
      }

      free(string_array->array[i]);
    }

    free(string_array->array);

    string_array->array = new_array;
    string_array->max_size = new_max_size;
  }

  int i;
  for (i = 0; i < strlen(to_add); ++i) {
    string_array->array[string_array->size][i] = to_add[i];
  }

  string_array->size += 1;
}

void dynamic_string_array_pop(dynamic_string_array_t *string_array, char *result)
{
  strncpy(result, string_array->array[ string_array->size - 1 ], strlen(string_array->array[ string_array->size - 1 ]));
  result[ strlen(string_array->array[ string_array->size - 1 ]) ] = 0;

  --string_array->size;
}

void dynamic_string_array_clear(dynamic_string_array_t *string_array)
{
  int i;
  for (i = 0; i < string_array->max_size; ++i) {
    free(string_array->array[i]);
  }

  free(string_array->array);
}
