#include <stdio.h>
#include <dirent.h>
#include <string.h>

#ifndef TOOLS_H
#define TOOLS_H

#include "config.h"

int readFilelist(const char*, char[MAX_FLIST_LEN][FILENAME_MAX]);
void str_replace(char *source, char *substr, char *replace);

#endif