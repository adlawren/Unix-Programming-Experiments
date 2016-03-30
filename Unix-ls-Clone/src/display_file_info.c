#include "display_file_info.h"

void print_permissions(struct stat *buf) {
  if (S_ISDIR((*buf).st_mode)) {
    printf("d");
  } else if (S_ISLNK((*buf).st_mode)) {
    printf("l");
  } else {
    printf("-");
  }

  printf(((*buf).st_mode & S_IRUSR) ? "r" : "-");
  printf(((*buf).st_mode & S_IWUSR) ? "w" : "-");
  printf(((*buf).st_mode & S_IXUSR) ? "x" : "-");
  printf(((*buf).st_mode & S_IRGRP) ? "r" : "-");
  printf(((*buf).st_mode & S_IWGRP) ? "w" : "-");
  printf(((*buf).st_mode & S_IXGRP) ? "x" : "-");
  printf(((*buf).st_mode & S_IROTH) ? "r" : "-");
  printf(((*buf).st_mode & S_IWOTH) ? "w" : "-");
  printf(((*buf).st_mode & S_IXOTH) ? "x" : "-");
}

void display_file_info(const char *filename)
{
  struct stat buf;

  if (lstat(filename, &buf) < 0) {
    fprintf(stderr, "stat error: %s\n", strerror(errno));
    return;
  }

  // Print permissions
  print_permissions(&buf);
  printf("\t");

  printf("%u\t", (size_t) buf.st_nlink);

  struct passwd *pwd = getpwuid(buf.st_uid);
  printf("%s\t", pwd->pw_name);

  struct group *grp = getgrgid(buf.st_gid);
  printf("%s\t", grp->gr_name);

  printf("%u\t", (size_t) buf.st_size);

  char buffer[2048];
  strftime(buffer, 2048, "%b %d %H:%M", localtime(&(buf.st_mtime)));
  printf("%s\t", buffer);

  int i;
  for (i = 0; i < strlen(filename); ++i) {
    buffer[i] = filename[i];
  }
  buffer[ strlen(filename) ] = 0;

  char *token = strtok(buffer, "/"), *prev_token = 0;
  while ((token = strtok(0, "/")) != 0) {
    prev_token = token;
  }

  printf("%s", prev_token);

  // Determine the type of file
  char *ptr = 0;
  if (S_ISDIR(buf.st_mode)) {
    ptr = "/";
  } else if (S_ISCHR(buf.st_mode)) {
    ptr = "character special";
  } else if (S_ISBLK(buf.st_mode)) {
    ptr = "block special";
  } else if (S_ISFIFO(buf.st_mode)) {
    ptr = "|";
  } else if (S_ISLNK(buf.st_mode)) {
    ptr = "@";
  } else if (S_ISSOCK(buf.st_mode)) {
    ptr = "=";
  } else if (S_ISREG(buf.st_mode) && buf.st_mode & 0111) {
    ptr = "*";
  }

  if (ptr) printf("%s", ptr);

  printf("\n");
}
