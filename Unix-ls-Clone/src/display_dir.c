#include "display_dir.h"

void display_dir(const char *dirname)
{
  printf("%s:\n", dirname);

  // Local parameters
  int i; // Loop index
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

  struct dirent **file_list;
  int file_count = scandir(dirname, &file_list, 0, alphasort);

  // Build list of filenames in the directory
  dynamic_string_array_t string_array;
  dynamic_string_array_init(&string_array, 10, MAX_STRING_SIZE); // TODO: Refactor out constant

  size_t total_blocks = 0;

  // Build an array of the directory contents
  for (i = 0; i < file_count; ++i) {
    char full_path[MAX_PATH_LEN];
    strncpy(full_path, dirname, strlen(dirname));
    full_path[ strlen(dirname) ] = 0; // Prevent buffer overrun

    if (full_path[ strlen(dirname) - 1 ] != '/') {
      strcat(full_path, "/");
    }

    strcat(full_path, file_list[i]->d_name);

    if (lstat(full_path, &buf) < 0) {
      fprintf(stderr, "stat error: %s\n", strerror(errno));
      return;
    }

    total_blocks += (size_t) buf.st_blocks / 2;

    dynamic_string_array_push(&string_array, full_path);
  }

  printf("total %u\n", total_blocks);

  // Print the directory contents
  for (i = 0; i < string_array.size; ++i) {
    display_file_info(string_array.array[i]);
  }

  printf("\n");

  // Recurse through subdirectories
  for (i = 0; i < string_array.size; ++i) {
    char temp[MAX_STRING_SIZE];
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

  // Free the contents of the dynamic array
  dynamic_string_array_clear(&string_array);

  // Free the contents of the file list
  for (i = 0; i < file_count; ++i) {
    free(file_list[i]);
  }
  free(file_list);

  closedir(dp);
}
