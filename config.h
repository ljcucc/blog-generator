#include <stdio.h>

#ifndef CONFIG_H
#define CONFIG_H

#define MAX_FLIST_LEN 100

#define SUCCESS 0
#define FAIL 1
#define MAX_TXT_LEN 10000

static const char OUTPUT_FOLDER[FILENAME_MAX] =  "./public/";
static const char INPUT_FOLDER[FILENAME_MAX] =  "./md/";

#endif