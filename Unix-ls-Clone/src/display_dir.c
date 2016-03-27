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

  // Traverse the directory contents
  struct dirent *next_dirent;
  while ((next_dirent = readdir(dp))) {
    if ((strcmp(next_dirent->d_name, ".") == 0) || (strcmp(next_dirent->d_name, "..") == 0)) {
      continue;
    }

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

    display_file_info(full_path);

    if (S_ISDIR(buf.st_mode)) {
      display_dir(full_path);
    }
  }
}
