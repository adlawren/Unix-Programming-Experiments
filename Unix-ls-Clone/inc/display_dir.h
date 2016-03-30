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

// local
#include "common.h"
#include "dynamic_string_array.h"
#include "display_file_info.h"

void display_dir(const char *dirname);

#endif // __DISPLAY_DIR_H__
