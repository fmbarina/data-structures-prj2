#include "bits.h"
#include <stdio.h>
#include <stdlib.h>
#include "assertr.h"

/* This code is in large part a copy of Joao Paulo Andrade Almeida's
 * (jpalmeida@inf.ufes.br) "bitmap.h". We thought it might be useful
 * to alter the code so we could add or change functionality, but we
 * weren't sure that we could do so. Therefore, we decided to make a
 * new "bits.h" based on "bitmap.h". As most of the code was already
 * written, we just borrowed it from Joao's and slighly changed some
 * lines. Credit is given where due.
 */

struct bits_st
{
    unsigned int maxlen;
    unsigned int len;
    unsigned int cur;
    unsigned char *contents;
};

tBits *bits_init(unsigned int max_length)
{
    /* Original code by Joao Paulo Andrade Almeida (jpalmeida@inf.ufes.br) */
    tBits *bs;
    bs = (tBits *)malloc(sizeof(tBits));

    unsigned int max_size_in_bytes = (max_length + 7) / 8;
    bs->contents = calloc(max_size_in_bytes, sizeof(char));

    assertr(bs->contents != NULL, "Erro de alocacao de memoria.");

    bs->maxlen = max_length;
    bs->len = 0;
    bs->cur = 0;

    return bs;
}

void bits_free(tBits *bs)
{
    /* Original code by Joao Paulo Andrade Almeida (jpalmeida@inf.ufes.br) */
    assertr(bs != NULL, "free() mas tBits nunca alocado");
    free(bs->contents);
    free(bs);
}

void bits_append(tBits *bs, unsigned char bit)
{
    /* TODO: assertr(bit == (unsigned char)0 || bit == (unsigned char)1,
            "Bit precisa ser zero ou um");
    */
    /* Original code by Joao Paulo Andrade Almeida (jpalmeida@inf.ufes.br) */
    assertr(bs->len < bs->maxlen, "Tamanho maximo de tBits excedido");
    bs->len++;
    bits_set_bit(bs, bs->len - 1, bit);
}

unsigned char bits_read(tBits *bs)
{
    assertr(bs->cur < bs->len, "Tentativa de ler bit com cursor alem do maximo");

    unsigned char read = (bs->contents[bs->cur / 8] >> (7 - (bs->cur % 8))) & 0x01;

    bs->cur++;
    return read;
}

void bits_set_bit(tBits *bs, unsigned int idx, unsigned char bit)
{
    /* TODO: assertr(bit == (unsigned char)0 || bit == (unsigned char)1,
            "Bit precisa ser zero ou um");
    */
    /* Original code by Joao Paulo Andrade Almeida (jpalmeida@inf.ufes.br) */
    assertr(idx < bs->len, "Tentativa de definir bit fora de alcance");

    bit = bit & 0x01;
    bit = bit << (7 - (idx % 8));
    bs->contents[idx / 8] = bs->contents[idx / 8] | bit;
}

unsigned char bits_get_bit(tBits *bs, unsigned int idx)
{
    /* Original code by Joao Paulo Andrade Almeida (jpalmeida@inf.ufes.br) */
    assertr(idx < bs->len, "Acesso a posicao inexistente de tBits");

    return (bs->contents[idx / 8] >> (7 - (idx % 8))) & 0x01;
}

void bits_set_len(tBits *bs, unsigned int len)
{
    bs->len = len;
}

unsigned int bits_get_len(tBits *bs)
{
    return bs->len;
}

void bits_set_cur(tBits *bs, unsigned int cur)
{
    assertr(cur < bs->len, "tBits set cur maior que len");

    bs->cur = cur;
}

void bits_offset_cur(tBits *bs, unsigned int offset)
{
    assertr(bs->cur + offset < bs->len, "tBits offset cur maior que len");

    bs->cur += offset;
}

unsigned int bits_cur(tBits *bs)
{
    return bs->cur;
}

unsigned int bits_max(tBits *bs)
{
    return bs->maxlen;
}

unsigned char *bits_contents(tBits *bs)
{
    return bs->contents;
}

void bits_print(tBits *bs)
{
    printf("\n**BITS** : ");
    printf("MAX: %d LEN: %d CONTENTS: ", bs->maxlen, bs->len);

    unsigned int i;
    for (i = 0; i < bs->len; i++)
    {
        if (i && i % 8 == 0)
            printf(" ");

        unsigned char val = bs->contents[i / 8];
        printf("%d", ((val >> (7 - (i % 8))) & 0x01) ? 1 : 0);
    }
}