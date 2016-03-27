#include "main.h"

int main(int argc, char *argv[])
{
  if (argc > 1) {
    int i;
    for (i = 0; i < argc - 1; ++i) {

      // Iterate over the given directory
      display_dir(argv[i + 1]);
    }
  } else {
    
    // Iterate over the current directory
    display_dir(".");
  }

  return 0;
}
