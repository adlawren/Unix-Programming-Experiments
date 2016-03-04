#include "main.h"

int count_items(char *buffer)
{
  char *colon_separated = 0;
  strtok(buffer, ":");
  strtok(0, ":");
  colon_separated = strtok(0, ":");
  
  //printf("Colon separated: %s\n", colon_separated);

  int item_count = 0;
  char *comma_separated = strtok(colon_separated, ",");
  while (comma_separated)
  {
    ++item_count;
    comma_separated = strtok(0, ",");
  }

  //printf("Next item count: %d\n", item_count);

  return item_count;
}

int main(int argc, char *argv[])
{
  // Open the file.
  FILE *fp = 0;
  if ((fp = fopen(argv[1], "r")) == 0)
  {
    fprintf(stderr, "ERROR: The input file specified cannot be opened.\n");
    return -1;
  }

  int line_count = 0, item_count = 0;
  char buffer[256];
  while (fgets(buffer, 256, fp) != NULL)
  {
    //printf("Next line: %s", buffer);
    ++line_count;
    item_count += count_items(buffer);
  }

  printf("Summary:\n");
  printf("Line count: %d\n", line_count);
  printf("Item count: %d\n", item_count);
  return 0;
}
