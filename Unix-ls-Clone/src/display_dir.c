#include "display_dir.h"

void display_dir(const char *dirname)
{
  printf("%s:\n", dirname);

  // Local parameters
  struct stat buf;

  // Check if the provided path leads to a directory or not
  if (lstat(dirname, &buf) < 0) {
    fprintf(stderr, "stat error: %s\n", strerror(errno));
    return;
  }

  if (S_ISDIR(buf.st_mode) == 0) {
    fprintf(stderr, "ERROR: The given argument is not a directory.\n");
    return;
  }

  DIR *dp = opendir(dirname);
  if (!dp) {
    fprintf(stderr, "ERROR: Unable to open directory.\n");
    return;
  }

  // Build list of filenames in the directory
  size_t max_string_size = 2048;
  dynamic_string_array_t string_array;
  dynamic_string_array_init(&string_array, 10, max_string_size);

  size_t total_blocks = 0;

  // Build an array of the directory contents
  struct dirent *next_dirent;
  while ((next_dirent = readdir(dp))) {
    char full_path[MAX_PATH_LEN];
    strncpy(full_path, dirname, strlen(dirname));
    full_path[ strlen(dirname) ] = 0; // Prevent buffer overrun

    if (full_path[ strlen(dirname) - 1 ] == '/') {
      strcat(full_path, next_dirent->d_name);
    } else {
      strcat(full_path, "/");
      strcat(full_path, next_dirent->d_name);
    }

    if (lstat(full_path, &buf) < 0) {
      fprintf(stderr, "stat error: %s\n", strerror(errno));
      return;
    }

    total_blocks += (size_t) buf.st_blocks / 2;

    dynamic_string_array_push(&string_array, full_path);
  }

  dynamic_string_array_sort(&string_array);
  if (strcmp(string_array.array[0], ".")) {
    dynamic_string_array_swap(&string_array, 0, 1);
  }

  printf("total %u\n", total_blocks);

  // Print the directory contents
  int i;
  for (i = 0; i < string_array.size; ++i) {
    display_file_info(string_array.array[i]);
  }
  
  printf("\n");

  // Recurse through subdirectories
  for (i = 0; i < string_array.size; ++i) {
    char temp[max_string_size];
    int j;
    for (j = 0; j < strlen(string_array.array[i]); ++j) {
      temp[j] = string_array.array[i][j];
    }

    temp[ strlen(string_array.array[i]) ] = 0; // Prevent buffer overrun

    char *token = strtok(temp, "/"), *prev_token = 0;
    while ((token = strtok(0, "/")) != 0) {
      prev_token = token;
    }

    if ((strcmp(prev_token, ".") == 0) || (strcmp(prev_token, "..") == 0)) {
      continue;
    }

    if (lstat(string_array.array[i], &buf) < 0) {
      fprintf(stderr, "stat error: %s\n", strerror(errno));
      return;
    }
    
    if (S_ISDIR(buf.st_mode)) {
      display_dir(string_array.array[i]);
    }
  }

  dynamic_string_array_clear(&string_array);

  closedir(dp);
}
