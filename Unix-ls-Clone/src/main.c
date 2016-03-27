#include "main.h"

#include "dynamic_string_array_test.h"

int main(int argc, char *argv[])
{
  if (argc > 1) {
    printf("Arguments given\n");

    int i;
    for (i = 0; i < argc - 1; ++i) {
      
      // Iterate over the given directory
      display_dir(argv[i + 1]);
    }
  } else {
    printf("No arguments given\n");

    // Iterate over the current directory
    display_dir(".");
  }

  return 0;
}
