#include "main.h"

int main(int argc, char *argv[])
{ 
  // Ensure the appropriate number of command line arguments is provided.
  if (argc != 2)
  {
    fprintf(stderr, "ERROR: A single command line argument specifying the input file must be provided.\n");
    return -1;
  }

  // Open the file.
  FILE *fp = 0;
  if ((fp = fopen(argv[1], "r")) == 0)
  {
    fprintf(stderr, "ERROR: The input file specified cannot be opened.\n");
    return -1;
  }

  // Print the filename.
  printf("Input File: %s\n", argv[1]);

  // Parse file 
  char buffer[256];
  while (fgets(buffer, 256, fp) != NULL)
  {
    printf("Next Line: %s\n", buffer);

    // TODO: Display output.
    // ...
  }

  fclose(fp);

  return 0;
}
