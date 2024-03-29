#include "dynamic_string_array_test.h"

void run_tests() {
  char *to_add, popped[MAX_STRING_SIZE];
  size_t initial_max_size = 2,  max_string_size = MAX_STRING_SIZE;

  dynamic_string_array_t string_array;
  dynamic_string_array_init(&string_array, initial_max_size, max_string_size);

  assert(string_array.size == 0);
  assert(string_array.max_size == initial_max_size);

  to_add = "string 1";
  dynamic_string_array_push(&string_array, to_add);

  assert(string_array.size == 1);

  dynamic_string_array_pop(&string_array, popped);

  assert(string_array.size == 0);
  assert(strcmp(popped, to_add) == 0);

  to_add = "string a";
  dynamic_string_array_push(&string_array, to_add);

  to_add = "string c";
  dynamic_string_array_push(&string_array, to_add);

  assert(string_array.size == 2);
  assert(string_array.max_size == initial_max_size);

  to_add = "string b";
  dynamic_string_array_push(&string_array, to_add);

  assert(string_array.size == 3);
  assert(string_array.max_size == 2 * initial_max_size);

  dynamic_string_array_sort(&string_array);

  dynamic_string_array_pop(&string_array, popped);

  assert(string_array.size == 2);
  assert(strcmp(popped, "string c") == 0);

  dynamic_string_array_pop(&string_array, popped);

  assert(string_array.size == 1);
  assert(strcmp(popped, "string b") == 0);

  dynamic_string_array_pop(&string_array, popped);

  assert(string_array.size == 0);
  assert(strcmp(popped, "string a") == 0);

  dynamic_string_array_clear(&string_array);
}
