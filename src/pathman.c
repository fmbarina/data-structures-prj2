#include "pathman.h"
#include <stdlib.h>
#include <string.h>

/* Dir separator character */
#ifdef __unix__
#define DIR_DELIM  "/\0" 
#elif defined(_WIN32) || defined(WIN32)
#define DIR_DELIM  "\\0"
#endif

#define EXT_DELIM ".\0" /* Extension separator string */

static char *trim_end_path(char *path, int characters)
{
    char *new_path = (char*) malloc(strlen(path) - characters + 1);

    strncpy(new_path, path, strlen(path) - characters);
    new_path[strlen(path) - characters] = '\0';
    free(path);

    return new_path;
}

static char *trim_start_path(char *path, int characters)
{
    char *new_path = (char*) malloc(strlen(path) - characters + 1);

    strncpy(new_path, path + characters + 1, strlen(path) - characters);
    new_path[strlen(path) - characters] = '\0';
    free(path);

    return new_path;
}

static char *empty_str(char *path)
{
    char *new_path = (char*) calloc(1, sizeof(unsigned char));
    free(path);
    return new_path;
}

char *expth(char *path, char *add)
{
    char *new_path = malloc(strlen(path) + strlen(add) + 1);

    strcpy(new_path, path);
    strcat(new_path, add);
    free(path);

    return new_path;
}

char *trpth(char *path)
{
    unsigned int len = (unsigned int)strlen(path);
    
    if (len <= 2)
        return path;

    int i = len - 1;

    if (path[len - 1] == DIR_DELIM[0])
        i--;

    while (path[i] != DIR_DELIM[0])
        i--;

    return trim_end_path(path, len - i);
}

char *adpth(char *path, char *add)
{
    if (path[strlen(path) - 1] != DIR_DELIM[0])
        path = expth(path, DIR_DELIM);

    return expth(path, add);
}

char *trextpth(char *path)
{
    unsigned int len = (unsigned int)strlen(path);
    
    if (len <= 2)
        return path;

    int i = len - 1;

    while (path[i] != EXT_DELIM[0])
        i--;

    if (i == 0)
        return path;

    return trim_end_path(path, len - i);
}

char *getextpth(char *path)
{
    unsigned int len = (unsigned int)strlen(path);
    unsigned int i = 0;

    if (len <= 1)
        return path;    

    while (i < len && path[i] != EXT_DELIM[0])
        i++;

    if (i == len)
        return empty_str(path);

    return trim_start_path(path, i);
}

char* getnamepth(char* path)
{
    unsigned int len = (unsigned int)strlen(path);
    if (len <= 1)
        return path;

    path = trextpth(path);

    int i = len - 1;

    while (i > 0 && path[i] != DIR_DELIM[0])
        i--;

    if (i == 0)
        return path;
    else
        return trim_start_path(path, len - i);
}
