#include "compfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pathman.h"
#include "rwbin.h"
#include "bits.h"
#include "tree.h" 
#include "assertr.h"
#include "encoding.h"

/**
 * tCompfile structure
 *
 * Every compacted file (tCompfile) is written in blocks.
 *
 * All blocks except the signature are structured as:
 * - SIZE: 8-16 bits defining size
 * - DATA: 0-255 bytes or 0-N bits of data
 *
 * All compacted files contain:
 * BLOCK-01: ISO 8829-1 signature: EDH2
 * BLOCK-02: file name
 * BLOCK-03: file extension
 * BLOCK-05: file encoding
 * 
 * The encoded file contents are the remaining blocks:
 * BLOCK-xx: file contents (compressed)
 */

/* Magic numbers in ISO 8829-1 : E D H 2 */
static unsigned char signature[4] = {0x45, 0x44, 0x48, 0x32};
static unsigned char signature_size = 4;

struct compfile_st
{
    FILE *file;
    char *path;
    char *name;
    char *ext;
    tTree *tree;
};

tCompfile *comp_init()
{
    tCompfile *cf = (tCompfile *)malloc(sizeof(tCompfile));

    cf->path = NULL;
    cf->file = NULL;
    cf->name = NULL;
    cf->ext = NULL;

    return cf;
}

void comp_free(tCompfile *cf)
{
    assertr(cf != NULL, "free() mas tCompfile não foi alocado");

    if (cf->file != NULL)
        fclose(cf->file);

    if (cf->tree != NULL)
        tree_free(cf->tree);

    free(cf->path);
    free(cf->name);
    free(cf->ext);
    free(cf);
}

void comp_write_header(tCompfile *cf)
{
    assertr(cf->name != NULL, "tCompfile sem nome não pode ser escrito");
    assertr(cf->ext != NULL, "tCompfile sem extensão não pode ser escrito");

    /* Close old file & guard */
    if (cf->file)
        fclose(cf->file);
    cf->file = fopen(cf->path, "wb");
    assertr(cf->file != NULL, "tCompfile: nao pode abrir o arquivo");
    
    /* Sign file */
    wbin_magic_block(cf->file, signature, signature_size);

    /* Write name and extension to file */
    wbin_long_str_block(cf->file, cf->name);
    wbin_short_str_block(cf->file, cf->ext);

    /* Write the serialized tree encoding */
    tBits *bs = tree_serialize(cf->tree);
    wbin_bits_block(cf->file, bs);
    bits_free(bs);
}

unsigned int comp_write_data(tCompfile *cf, tBits *bs)
{
    assertr(cf->file != NULL, "escrevendo tCompfile: arquivo nao foi aberto");

    return wbin_bits_block(cf->file, bs);
}

void comp_read_header(tCompfile *cf)
{
    /* Close old file / safeguard */
    if (cf->file)
        fclose(cf->file);
    cf->file = fopen(cf->path, "rb");
    assertr(cf->file != NULL, "tCompfile: nao pode abrir o arquivo");

    /* Check file signature */
    assertr(rbin_magic_block(cf->file, signature, signature_size),
            "Arquivo incompatível, assinatura diferente");

    /* Read name and extension from the file */
    cf->name = rbin_long_str_block(cf->file);
    cf->ext = rbin_short_str_block(cf->file);

    /* Deserialize and build tree encoding */
    tBits *bs = bits_init(65355);
    rbin_bits_block(cf->file, bs);
    cf->tree = tree_deserialize(bs);
    bits_free(bs);
}

unsigned int comp_read_data(tCompfile *cf, tBits *bs)
{
    assertr(cf->file != NULL, "lendo tCompfile: arquivo nao foi aberto");

    return rbin_bits_block(cf->file, bs);
}

char *comp_get_path(tCompfile *cf)
{
    return cf->path;
}

void comp_set_path(tCompfile *cf, char *path)
{
    cf->path = strdup(path);
}

char *comp_get_name(tCompfile *cf)
{
    return cf->name;
}

void comp_set_name(tCompfile *cf, char *name)
{
    cf->name = strdup(name);
}

char *comp_get_ext(tCompfile *cf)
{
    return cf->ext;
}

void comp_set_ext(tCompfile *cf, char *ext)
{
    cf->ext = strdup(ext);
}

tTree *comp_get_tree(tCompfile *cf)
{
    return cf->tree;
}

void comp_set_tree(tCompfile *cf, tTree* tr)
{
    cf->tree = tr;
}