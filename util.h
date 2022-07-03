#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "config.h"

#ifndef TOOLS_H
#define TOOLS_H

char *inputFolder;
char *outputFolder;
char *templateFolder;

int readFilelist(const char*, char[MAX_FLIST_LEN][FILENAME_MAX]);
void str_replace(char *source, char *substr, char *replace);

typedef struct Filelist{
  int filelist_size;
  char filename_list[MAX_FLIST_LEN][FILENAME_MAX];
} Filelist;

#endif
