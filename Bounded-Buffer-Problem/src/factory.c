#include "factory.h"

// TODO: remove; test
void *test_function(void *args)
{
  long id = (long) args;

  // TODO: remove test
  printf("I'm thread %lu\n", id);

  pthread_exit(0);
}

int main(int argc, char *argv[])
{ 
  // Ensure the appropriate number of command line arguments is provided.
  if (argc != 6)
  {
    fprintf(stderr, "ERROR: Five command line arguments must be given.\n");
    return -1;
  }

  // Place the command line parameters into the respective variables
  char *temp;
  unsigned a = strtol(argv[1], &temp, 10),
    p = strtol(argv[2], &temp, 10),
    l = strtol(argv[3], &temp, 10),
    n = strtol(argv[4], &temp, 10),
    c = strtol(argv[5], &temp, 10);

  // TODO: remove; test
  printf("%d %d %d %d %d\n", a, p, l, n, c);

  // Create assembler threads
  pthread_t assembler_threads[a];
  long assembler_thread_ids[a];

  int i = 0;
  for (i = 0; i < a; ++i)
  {
    assembler_thread_ids[i] = i;
    if (pthread_create(&assembler_threads[i], 0, test_function, (void *) assembler_thread_ids[i]))
    {
      fprintf(stderr, "ERROR: pthread creation failed\n");
      return -1;
    }
  }

  // Create packer threads
  // ...

  // Wait for the packer threads to complete
  // ...

  pthread_exit(0);

  return 0;
}
