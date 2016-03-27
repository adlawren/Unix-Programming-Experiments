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

int char_compare(char c1, char c2) {
  // int i1 = (int) c1, i2 = (int) c2;
  if (c1 < c2) {
    return 1;
  } else if (c1 > c2) {
    return -1;
  } else {
    return 0;
  }
}

void string_to_lower(const char *str, char *lower)
{
  int i;
  for (i = 0; i < strlen(str); ++i) {
    lower[i] = tolower(str[i]);
  }

  lower[ strlen(str) ] = 0;
}

int string_compare(const char *str1, const char *str2) {
  size_t min_len = strlen(str1);
  if (strlen(str2) < min_len) min_len = strlen(str2);

  char lower1[2048], lower2[2048];
  string_to_lower(str1, lower1);
  string_to_lower(str2, lower2);

  int i;
  for (i = 0; i < min_len; ++i) {
    if (char_compare(lower1[i], lower2[i])) {
      return char_compare(lower1[i], lower2[i]);
    }
  }

  return 0;
}

void dynamic_string_array_swap(dynamic_string_array_t *string_array, int idx1, int idx2)
{
  char *temp = string_array->array[idx1];
  string_array->array[idx1] = string_array->array[idx2];
  string_array->array[idx2] = temp;
}

void dynamic_string_array_sort(dynamic_string_array_t *string_array)
{
  int i, j;
  for (i = 0; i < string_array->size; ++i) {
    for (j = i + 1; j < string_array->size; ++j) {
      if (string_compare(string_array->array[i], string_array->array[j]) < 0) {
	dynamic_string_array_swap(string_array, i, j);
      }
    }
  }
}

void dynamic_string_array_clear(dynamic_string_array_t *string_array)
{
  int i;
  for (i = 0; i < string_array->max_size; ++i) {
    free(string_array->array[i]);
  }

  free(string_array->array);
}
