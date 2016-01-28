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
  printf("Sorting File: %s\n", argv[1]);

  // Read the integers from the input file into a shared int array.
  int *array = 0;
  char buffer[256];
  while (fgets(buffer, 256, fp) != NULL)
  {
    unsigned array_size = 0;
    array = parse_into_shared_int_array(buffer, &array_size);
    
    // Sort the array.
    int *sorted_array = get_shared_int_array(array_size);
   
    pid_t pid = 0;
    if ((pid = fork_merge_sort(sorted_array, array, 0, array_size)) <= 0)
    {
      return pid;
    }

    // Display output.
    printf("%d elements read\n\n", array_size);

    printf("Input Numbers:\n");
    print_array(array, array_size);
    printf("\n");

    printf("Sorted Numbers:\n");
    print_array(sorted_array, array_size);
    printf("\n");
  }

  fclose(fp);

  return 0;
}
