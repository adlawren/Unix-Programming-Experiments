#include "main.h"

// TODO: implement
int * parse_shared_int_array()
{
  return 0;
}

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

  // Read the line of input.
  char buffer[256];
  while (fscanf(fp, "%s", buffer) != EOF)
  {
    printf("Next line: %s\n", buffer);
  }

  

  // Initialize shared memory.
  void *array = 0;
  const int SIZE = 8;
  if ((array = mmap(0, SIZE * sizeof(int), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0)) == 0)
  {
    printf("ERROR: failed to initailize shared memory.\n");
    return -1;
  }

  // -----------------
  // TODO: Remove; test
  /*
  int * int_array = (int *) array;
  int i = 0;
  for (i = 0; i < SIZE; ++i)
  {
    int_array[i] = i;
  }

  // Ensure the memory is accessible from a child.
  pid_t pid = fork();
  if (pid == 0)
  {
    // Child code.
    int j = 0;
    for (j = 0; j < SIZE; ++j)
    {
      printf("Next int: %d\n", int_array[j]);
    }

    printf("Exited loop.\n");

    return 0;
  }
  else if (pid != -1)
  {
    // Parent code.
    // ...
  }
  else
  {
    fprintf(stderr, "ERROR: fork() failed.\n");
    return -1;
  }

  // Ensure the function signature can be envoked.
  int sorted_array_test[SIZE];
  merge_sort(sorted_array_test, int_array, 0, SIZE);
  */
  // -----------------

  pid_t pid = 0;
  if ((pid = run_tests()) <= 0)
  {
    return 0;
  }

  // ...

  return 0;
}
