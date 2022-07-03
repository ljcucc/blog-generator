#if defined(_WIN32) || defined(_WIN64)
  #error Windows is not supported
#endif

#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "toc.h"
#include "config.h"
//
// https://stackoverflow.com/questions/164194/why-do-i-get-a-segmentation-fault-when-writing-to-a-char-s-initialized-with-a
// https://stackoverflow.com/questions/15926129/char-vs-char-c-for-accessing-a-string-array

void renderHomepageTOC(Filelist*);
int init(Filelist*fl);
int renderWithPandoc(char *filename);

void renderHomepageTOC(Filelist*md_list)
{
  char HTML_codes[MAX_TXT_LEN], cmd[100];

  // copying index.html from template by command
  snprintf(cmd, 100, "cp %s/index.html %s",templateFolder ,outputFolder);
  system(cmd);

  printf("reading index.html...\n");

  // generate path of index.html in output folder
  char path[300];
  snprintf(path, 100, "%s/index.html", outputFolder);
  puts(path);

  FILE *fileIn, *fileOut;

  // open for reading index.html
  if ((fileIn = fopen(path, "r")) == NULL)
  {
    printf("Could not open index.html\n");
    exit(1);
  }

  /* Getting each line */
  char inputBuff[MAX_TXT_LEN];
  while (fgets(inputBuff, sizeof(inputBuff), fileIn))
  {
    strncat(HTML_codes, inputBuff, sizeof(inputBuff));
  }

  char tocBuffer[MAX_TXT_LEN];

  /* Generate TOC HTMLs from FileList */
  generateTocHtml(tocBuffer, md_list);

  /* replacing template slot */
  str_replace(HTML_codes, "$toc$", tocBuffer);

  /* close reading FILE */
  if (fclose(fileIn) == EOF)
  {
    puts("file close error\n");
    exit(1);
  }

  /* open for writing */
  if ((fileOut = fopen(path, "w+")) == NULL)
  {
    printf("Could not open index.html");
    exit(1);
  }

  /* write new result to index.html */
  fputs(HTML_codes, fileOut);

  /* close output FILE */
  if (fclose(fileOut) == EOF)
  {
    puts("file close error\n");
    exit(1);
  }
}

int renderWithPandoc(char *filename)
{
  char cmd[100];

  printf("* Rendering %s\n", filename);

  snprintf(cmd, 100, "");

  return SUCCESS;
}

int init(Filelist*fl)
{
  char cmd[100];

  printf("initialing...\n");

  printf("initialing output folder...\n");

  snprintf(cmd, 100, "rm -rf %s", outputFolder);
  system(cmd);

  snprintf(cmd, 100, "mkdir -p %s", outputFolder);
  system(cmd);

  renderHomepageTOC(fl);

  printf("initial done!\n");

  return SUCCESS;
}

int checkCmdFormat(int argc)
{
  if (argc != 4)
  {
    printf("Arguments format error.\n");
    exit(1);
  }
}

int main(int argc, char **argv)
{
  Filelist md_list;
  // char md_list[MAX_FLIST_LEN][FILENAME_MAX];

  checkCmdFormat(argc);

  // read from args input
  inputFolder = argv[1];
  outputFolder = argv[2];
  templateFolder = argv[3];

  printf("Rendering each page...\n");

  md_list.filelist_size = readFilelist(inputFolder, md_list.filename_list);

  // init with commands
  init(&md_list);

  for (int i = 0; i < md_list.filelist_size; i++)
  {
    renderWithPandoc(md_list.filename_list[i]);
  }

  printf("done!\n");

  return 0;
}
