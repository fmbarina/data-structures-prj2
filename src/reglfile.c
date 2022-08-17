#include "reglfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bytes.h"
#include "assertr.h"
#include "pathman.h"

struct reglfile_st
{
    FILE *file;
    char *path;
    char *name;
    char *ext;
};

tReglfile *regl_init()
{
    tReglfile *rf = (tReglfile *)malloc(sizeof(tReglfile));

    rf->path = NULL;
    rf->name = NULL;
    rf->ext = NULL;

    return rf;
}

void regl_free(tReglfile *rf)
{
    assertr(rf != NULL, "free() mas tReglfile não foi alocado");

    if (rf->file != NULL)
        fclose(rf->file);
    
    free(rf->path);
    free(rf->name);
    free(rf->ext);
    free(rf);
}

unsigned int regl_read_bytes(tReglfile *rf, tBytes *bt)
{
    assertr(rf->path != NULL, "Impossivel ler tReglfile com path: NULL");

    if (rf->file == NULL)
        rf->file = fopen(rf->path, "rb");
    assertr(rf->file != NULL, "tReglfile: nao pode abrir o arquivo");

    unsigned int read = fread(bytes_contents(bt), sizeof(unsigned char), bytes_max(bt), rf->file);
    bytes_set_len(bt, read);

    return read;
}

unsigned int regl_write_bytes(tReglfile *rf, tBytes *bt)
{
    assertr(rf->path != NULL, "Impossivel escrever tReglfile com path: NULL");

    if (rf->file == NULL)
        rf->file = fopen(rf->path, "wb");
    assertr(rf->file != NULL, "tReglfile: nao pode abrir o arquivo");

    return fwrite(bytes_contents(bt), sizeof(unsigned char), bytes_get_len(bt), rf->file);
}

int regl_read_single_byte(tReglfile *rf, unsigned char *byte)
{
    if (rf->file == NULL)
        rf->file = fopen(rf->path, "rb");
    assertr(rf->file != NULL, "tReglfile: nao pode abrir o arquivo");

    return fscanf(rf->file, "%c", byte);
}

void regl_reset_cursor(tReglfile *rf)
{
    fseek(rf->file, 0, SEEK_SET);
}

char *regl_get_path(tReglfile *rf)
{
    return rf->path;
}

void regl_set_path(tReglfile *rf, char *path)
{
    rf->path = strdup(path);
}

char *regl_get_name(tReglfile *rf)
{
    return rf->name;
}

void regl_set_name(tReglfile *rf, char *name)
{
    rf->name = strdup(name);
}

char *regl_get_ext(tReglfile *rf)
{
    return rf->ext;
}

void regl_set_ext(tReglfile *rf, char *ext)
{
    rf->ext = strdup(ext);
}

void regl_guess_name_ext(tReglfile *rf)
{
    assertr(rf->path != NULL, "tReglfile path NULL: nao pode gerar name/ext");
    rf->name = getnamepth(strdup(rf->path));
    rf->ext = getextpth(strdup(rf->path));
}