// STD libs
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Third-party libraries
#include "libs/cJSON.h"

// Local header files
#include "toc.h"
#include "config.h"

#define MAX_CMD_LEN 2048

/* slots name by order: filename, headerImg(path), title, created */
#define TOC_ITEM_TEMPLATE \
" <div class=\"card\" onclick=\"location.href=`/%s`\"> \n \
    <div class=\"header\"> \n \
      %s \n \
    </div> \n \
    <div class=\"description\"> \n \
      <div class=\"title\">%s</div> \n \
      <div class=\"date\">%s</div> \n \
    </div> \n \
  </div> \n \
"

#define TOC_IMG_HEADER_TEMPLATE "      <img src=\"%s\"/> \n"

typedef struct {
  char filename[MAX_FLIST_LEN];
  char title[MAX_FLIST_LEN];
  bool public;
  char headerImg[MAX_FLIST_LEN];
  char date[MAX_FLIST_LEN];
} Metadata;

void new_MDFromJson(cJSON*json, Metadata*md){
  /* cjson var to store temp value */
  cJSON*node;

  /* initial optional value */
  md->headerImg[0] = '\0'; // set to empty string 
  md->date[0] = '\0'; // set to empty string

  /* set title to md.title */
  node = cJSON_GetObjectItemCaseSensitive(json, "title");
  if(cJSON_IsString(node) && (node->valuestring != NULL)){
    strncpy(md->title, node->valuestring, sizeof(md->title));
  }

  // set public boolean to md.public
  node = cJSON_GetObjectItemCaseSensitive(json, "public");
  if(cJSON_IsTrue(node)){
    md->public = true;
  }

  // set header image path to md.headerImg
  node = cJSON_GetObjectItemCaseSensitive(json, "header-img");
  if(cJSON_IsString(node) && (node->valuestring != NULL)){
    strncpy(md->headerImg, node->valuestring, sizeof(md->headerImg));
  }

  // get date from string
  node = cJSON_GetObjectItemCaseSensitive(json, "date");
  if(cJSON_IsString(node) && (node->valuestring != NULL)){
    strncpy(md->headerImg, node->valuestring, sizeof(md->headerImg));
  }
}

void initMetadataTemplate(const char*filename, char*result){
  FILE*fp;
  char cmd[MAX_CMD_LEN], buff[2048];

  // creating template
  system("echo '$meta-json$' > /tmp/metadata.pandoc-tpl");

  // Set commands by template to cmd buffer
  snprintf(cmd, sizeof(cmd), "pandoc --template=/tmp/metadata.pandoc-tpl %s/%s", inputFolder, filename);

  // Trying to run command
  if((fp = popen(cmd, "r")) == NULL) 
  {
    printf("Failed to run command\n" );
    exit(1);
  }

  result[0] = '\0';
  while (fgets(buff, MAX_TXT_LEN, fp) != NULL) {
    strncat(result, buff, MAX_TXT_LEN);
  }
}

void getMetadata(const char* filename, Metadata*md){
  // Read command from result
  char result[MAX_TXT_LEN];

  initMetadataTemplate(filename, result);

  // Parsing command by using cJSON
  cJSON *json;
  if((json = cJSON_Parse(result)) == NULL){
    puts("JSON parsing error");
    exit(1);
  }

  // Setup Metadata from json
  new_MDFromJson(json, md);

  // Delete JSON Data from heap
  cJSON_Delete(json);
}

void getItemTemplateString(char* buff, Metadata*md){
  char temp[MAX_TXT_LEN];

  if(!md->public) return;


  /* imageHeader template */
  char imageHeaderHTML[MAX_TXT_LEN];
  imageHeaderHTML[0] = '\0';

  if(md->headerImg[0] != '\0'){
    snprintf(imageHeaderHTML, sizeof(imageHeaderHTML),TOC_IMG_HEADER_TEMPLATE);
  }

  // slots name by order: filename, headerImg(path), title, created
  snprintf(temp, sizeof(temp), TOC_ITEM_TEMPLATE, 
      md->filename,
      imageHeaderHTML,
      md->title,
      md->date);

  puts(temp);

  strncat(buff, temp, MAX_TXT_LEN);
}

void generateTocHtml(char* buffer, Filelist*fl)
{
  printf("Genetating TOC...\n");
  for(int i = 0; i < fl->filelist_size; i++){
    char*filename = fl->filename_list[i];
    Metadata md;

    strncpy(md.filename, filename, sizeof(md.title));
    getMetadata(filename,&md);

    getItemTemplateString(buffer, &md);
    printf("Generated %s\n", filename);
  }
}
