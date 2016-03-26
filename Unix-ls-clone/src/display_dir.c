#include "display_dir.h"

void display_dir(const char *dirname)
{
  // TODO: Remove; test
  printf("Display dir invoked with argument: %s\n", dirname);

  struct stat buf;
  if (lstat(dirname, &buf) < 0) {
    fprintf(stderr, "stat error: %s\n", strerror(errno));
    return;
  }

  char *ptr;
  if (S_ISREG(buf.st_mode))       ptr = "regular";
  else if (S_ISDIR(buf.st_mode))  ptr = "directory";
  else if (S_ISCHR(buf.st_mode))  ptr = "character special";
  else if (S_ISBLK(buf.st_mode))  ptr = "block special";
  else if (S_ISFIFO(buf.st_mode)) ptr = "fifo";
  else if (S_ISLNK(buf.st_mode))  ptr = "symbolic link";
  else if (S_ISSOCK(buf.st_mode)) ptr = "socket";
  else                            ptr = "** unknown mode **";
  printf("%s\n", ptr);

  // Check if the provided path leads to a directory or not
  if (S_ISDIR(buf.st_mode) == 0) {
    return;
  }

  DIR *dp = opendir(dirname);
  if (!dp) {
    fprintf(stderr, "ERROR: Unable to open directory.\n");
    return;
  }

  struct dirent *next_dirent;
  while ((next_dirent = readdir(dp))) {
    if ((strcmp(next_dirent->d_name, ".") == 0) || (strcmp(next_dirent->d_name, "..") == 0)) {
      continue;
    }

    // Check if the given file system item is a file
    if (0) {

      // ...
    } else {
      char full_path[MAX_PATH_LEN];
      strncpy(full_path, dirname, strlen(dirname));
      full_path[ strlen(dirname) ] = 0; // Prevent buffer overrun

      if (full_path[ strlen(dirname) - 1 ] == '/') {
        strcat(full_path, next_dirent->d_name);
      } else {
	strcat(full_path, "/");
	strcat(full_path, next_dirent->d_name);
      }

      display_dir(full_path);
    }
  }
}
