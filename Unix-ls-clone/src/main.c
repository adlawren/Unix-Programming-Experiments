#include "main.h"

int main(int argc, char *argv[])
{
  if (argc > 1) {
    printf("Arguments given\n");

    int i;
    for (i = 0; i < argc - 1; ++i) {
      
      // Iterate over the given directory
      display_dir(argv[i + 1]);
    }
  } else {
    printf("No arguments given\n");

    // Iterate over the current directory
    display_dir(".");
  }

  return 0;
}

/*
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int i;
  struct stat buf;
  char *ptr;
  for (i = 1; i < argc; i++) {
    printf("%s: ", argv[i]);
    if (lstat(argv[i], &buf) < 0) {
      perror("stat error");
      continue;
    }
    if (S_ISREG(buf.st_mode))       ptr = "regular";
    else if (S_ISDIR(buf.st_mode))  ptr = "directory";
    else if (S_ISCHR(buf.st_mode))  ptr = "character special";
    else if (S_ISBLK(buf.st_mode))  ptr = "block special";
    else if (S_ISFIFO(buf.st_mode)) ptr = "fifo";
    else if (S_ISLNK(buf.st_mode))  ptr = "symbolic link";
    else if (S_ISSOCK(buf.st_mode)) ptr = "socket";
    else                            ptr = "** unknown mode **";
    printf("%s\n", ptr);
  }
  exit(0);
}
*/
