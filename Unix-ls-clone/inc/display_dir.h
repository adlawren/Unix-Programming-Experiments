#ifndef __DISPLAY_DIR_H__
#define __DISPLAY_DIR_H__

// std
#include "stdio.h"
#include "stdlib.h"

// sys
#include "sys/stat.h"

// misc
#include "dirent.h"
#include "string.h"
#include "errno.h"

#define MAX_PATH_LEN 2048

void display_dir(const char *dirname);

#endif // __DISPLAY_DIR_H__
