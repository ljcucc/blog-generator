#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include "util.h"

// string replace function same as in js: str_obj.replace(substr, replace);
void str_replace(char *source, char *substr, char *replace)
{
  char *found = strnstr(source, substr, MAX_TXT_LEN);
  if(found == NULL) return;

  char tail[MAX_TXT_LEN];

  strncpy(tail, found + strlen(substr), MAX_TXT_LEN);

  strncpy(found, replace, MAX_TXT_LEN/2);
  strncat(found, tail, MAX_TXT_LEN/2);

  // int index = found - source;
}

int readFilelist(const char *folderName, char filelist[MAX_FLIST_LEN][FILENAME_MAX])
{
  DIR *d;
  struct dirent *dir;

  int filelist_len = 0;

  if ((d = opendir(folderName)))
  {
    while ((dir = readdir(d)) != NULL)
    {
      if (dir->d_type == DT_REG)
      { // if file type is regular
        char *path = &filelist[filelist_len++];
        strncpy(path, dir->d_name, FILENAME_MAX);
      }
      // else file type ignored
    }
    closedir(d);
  }
  return filelist_len; // read failed
}
