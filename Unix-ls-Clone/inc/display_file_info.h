#ifndef __DISPLAY_FILE_INFO_H__
#define __DISPLAY_FILE_INFO_H__

// std
#include "stdio.h"
//#include "stdlib.h"
#include "unistd.h"

// sys
#include "sys/stat.h"
#include "sys/types.h"

// misc
#include "errno.h"
#include "string.h"
#include "pwd.h"
#include "grp.h"
#include "time.h"

// local
#include "common.h"

void display_file_info(const char *filename);

#endif // __DISPLAY_FILE_INFO_H__
