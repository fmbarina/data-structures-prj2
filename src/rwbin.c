/**
 * @file rwbin.c
 * @author Felipe M. Barina
 * @author Vitor F. Calmon
 * @brief 
 * @version 0.1
 * @date 2022-08-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "rwbin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bits.h"

/*
 * Generally speaking, a short would be half of an int, so if the int is 32
 * bits, the short could be 16. But this depends on the architecture and
 * compiler used.
 *
 * What this means for this software is that files written in one system
 * may be incompatible with the same software on other systems. This is
 * due to my lack of experience necessary to implement a better solution.
 */

/* Maximum long string (char*)
 * The maximum value for an unsigned short is usually 65535 (16 bits)
 * You may set a lower value, but don't go above this.
 */
#define M_LSTR 65535

void wbin_magic_block(FILE *f, unsigned char *signature, unsigned char size)
{
    fwrite(signature, sizeof(unsigned char), size, f);
}

void wbin_short_str_block(FILE *f, char *str)
{
    unsigned char size[1] = {strnlen(str, 255)};

    if (size[0] >= 255)
    {
        printf("\nString '%s'  muito grande (>=255).", str);
        printf("\nCaracteres excedentes serão ignorados.");
    }

    fwrite(size, sizeof(unsigned char), 1, f);

    if (size[0] > 0)
        fwrite(str, sizeof(unsigned char), size[0], f);
}

void wbin_long_str_block(FILE *f, char *str)
{
    unsigned short int size[1] = {strnlen(str, M_LSTR)};

    if (size[0] >= M_LSTR)
    {
        printf("\nString '%.200s'  muito grande (>=%d).", str, M_LSTR);
        printf("\nCaracteres excedentes serão ignorados.");
    }

    fwrite(size, sizeof(unsigned short int), 1, f);

    if (size[0] > 0)
        fwrite(str, sizeof(unsigned char), size[0], f);
}

unsigned int wbin_bits_block(FILE *f, tBits *bs)
{
    unsigned int size[1] = {bits_get_len(bs)};

    fwrite(size, sizeof(unsigned int), 1, f);

    size[0] = ((size[0] + 7) / 8);

    if (size[0] > 0)
        return fwrite(bits_contents(bs), sizeof(unsigned char), size[0], f);

    return 0;
}

int rbin_magic_block(FILE *f, unsigned char *signature, unsigned char size)
{
    unsigned char *buf = (unsigned char *)calloc(size, sizeof(unsigned char));

    fread(buf, sizeof(unsigned char), size, f);
    int r = (!strncmp((char *)buf, (char *)signature, size)) ? 1 : 0;
    free(buf);

    return r;
}

char *rbin_short_str_block(FILE *f)
{
    unsigned char size[1] = {0};
    char *str = (char *)calloc(255, sizeof(char));

    fread(size, sizeof(unsigned char), 1, f);

    if (size[0] > 0)
        fread(str, sizeof(unsigned char), size[0], f);

    return str;
}

char *rbin_long_str_block(FILE *f)
{
    unsigned short int size[1] = {0};
    char *str = (char *)calloc(M_LSTR, sizeof(char));

    fread(size, sizeof(unsigned short int), 1, f);

    if (size[0] > 0)
        fread(str, sizeof(unsigned char), size[0], f);

    return str;
}

unsigned int rbin_bits_block(FILE *f, tBits * bs)
{
    unsigned int size[1] = {0};
    unsigned int ret = 0;

    fread(size, sizeof(unsigned int), 1, f);

    if (size[0] > 0)
    {
        unsigned int bytes = ((size[0] + 7) / 8);

        unsigned char *values = (unsigned char *)
            calloc(bytes, sizeof(unsigned char));

        ret = fread(values, sizeof(unsigned char), bytes, f);

        unsigned int i;
        for (i = 0; i < size[0]; i++)
        {
            unsigned char val = values[i / 8];
            bits_append(bs, val >> (7 - (i % 8)));
        }

        free(values);
    }

    return ret;
}
