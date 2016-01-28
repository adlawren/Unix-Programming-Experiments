#include "main.h"

int * parse_into_shared_int_array(char *line, unsigned *array_size)
{
  // Use linked list to buffer the integers
  int_list list;
  int_list_init(&list);

  char *temp;
  char *token = strtok(line, " ");
  while (token)
  {
    int_list_add(&list, (int) strtol(token, &temp, 10));
    token = strtok(NULL, " ");
  }

  *array_size = list.size;

  // Initialize shared memory.
  void *array = 0;
  if ((array = mmap(0, list.size * sizeof(int), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0)) == 0)
  {
    printf("ERROR: failed to initailize shared memory.\n");
    return 0;
  }
  
  int *int_array = (int *) array;

  int i = 0;
  while (list.head)
  {
    int_array[i++] = list.head->data;
    int_list_remove(&list, list.head->data);
  }

  return int_array;
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

  printf("Sorting File: %s\n", argv[1]);

  // Read the integers from the input file into a shared int array.
  int *array = 0;
  char buffer[256];
  while (fgets(buffer, 256, fp) != NULL)
  {
    // printf("Next line: %s", buffer);

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
