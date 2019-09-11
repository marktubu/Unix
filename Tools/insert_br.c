#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX 256

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

bool isemptyline(char* str)
{
    char* ret = trimwhitespace(str);
    printf("is empty line %s", ret);
    if(ret != NULL && ret[0] == '\0')
    {
        return true;
    }

    return false;
}

int main(int argc, char ** argv)
{
    if(argc < 2)
    {
        printf("no file name input.");
        exit(1);
    }

    char* filename = argv[1];
    char* tempname = "temp.md";

    FILE* srcfile = fopen(filename, "r");
    if(srcfile == NULL)
    {
        printf("file not exists");
        exit(1);
    }
    
    FILE* dstfile = fopen(tempname, "w+");
    if(dstfile == NULL)
    {
        printf("file not exists");
        exit(1);
    }

    char* tmpstr = (char*) malloc(256);
    size_t buffersize = MAX;

    while (!feof(srcfile))
    {
        strcpy(tmpstr, "\0");
        //fgets(tmpstr, MAX, srcfile);
        getline(&tmpstr, &buffersize, srcfile);

        if(isemptyline(tmpstr))
        {
            printf("empty line");
            fprintf(dstfile, "%s", "</br>");
        }
        else
        {
            printf("not empty line");
            fprintf(dstfile, "%s\r\n", tmpstr);
        }
    }
    
    fclose(srcfile);
    fclose(dstfile);
    remove(filename);
    rename(tempname, filename);

    return 0;
}
