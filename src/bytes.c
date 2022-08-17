#include "bytes.h"
#include <stdio.h>
#include <stdlib.h>
#include "assertr.h"

struct bytes_st
{
    unsigned int maxlen;
    unsigned int len;
    unsigned int cur;
    unsigned char* contents;
};

tBytes* bytes_init(unsigned int max_length)
{
    tBytes* bt = (tBytes*) malloc(sizeof(tBytes));
    bt->contents = (unsigned char*) calloc(max_length, sizeof(unsigned char));
    bt->maxlen = max_length;
    bt->len = 0;
    bt->cur = 0;
    return bt;
}

void bytes_free(tBytes* bt)
{
    assertr(bt != NULL, "free() mas tBytes nunca foi alocado");

    free(bt->contents);
    free(bt);
}

void bytes_append(tBytes* bt, unsigned char byte)
{
    assertr(bt->len < bt->maxlen, "tBytes cheio, não há como acrescentar");

    bt->contents[bt->len++] = byte;
}

unsigned char bytes_read(tBytes* bt)
{
    assertr(bt->cur < bt->maxlen, "tBytes cursor chegou ao fim");

    return bt->contents[bt->cur++];
}

void bytes_set_byte(tBytes* bt, unsigned int idx, unsigned char byte)
{
    assertr(idx < bt->maxlen, "set() índice maior do que tBytes->maxlen");
    
    bt->contents[idx] = byte;
}

unsigned char bytes_get_byte(tBytes* bt, unsigned int idx)
{
    assertr(idx < bt->maxlen, "get() maior do que tBytes->maxlen");

    return bt->contents[idx];
}

void bytes_set_len(tBytes *bt, unsigned int len)
{
    bt->len = len;
}

unsigned int bytes_get_len(tBytes *bt)
{
    return bt->len;
}

unsigned int bytes_max(tBytes* bt)
{
    return bt->maxlen;
}

unsigned char* bytes_contents(tBytes* bt)
{
    return bt->contents;
}

void bytes_print(tBytes *bt)
{
    printf("\n**BYTES** : ");
    printf("MAX: %d LEN: %d CONTENTS: ", bt->maxlen, bt->len);

    unsigned int i;
    for (i = 0; i < bt->len; i++)
        printf("%d ", bt->contents[i]);
}