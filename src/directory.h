#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

int file_count(const char *name);
char **file_list(const char *name);

#endif /* __DIRECTORY_H__ */
