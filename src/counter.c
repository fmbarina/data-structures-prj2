#include "counter.h"
#include <stdio.h>
#include <stdlib.h>
#include "assertr.h"

/* long long int came in the C99 standard.
 * We could consider using just long,
 * or other big number store methods.
 * For now, this works.
 */

struct counter_st
{
    unsigned long long int *vet;
};

tCounter *counter_init()
{
    tCounter *co = malloc(sizeof(tCounter));

    unsigned long long int *v =
        (unsigned long long int *)
            calloc(256, sizeof(unsigned long long int));

    co->vet = v;

    return co;
}

void counter_free(tCounter *co)
{
    free(co->vet);
    free(co);
}

void *counter_byte_inc(tCounter *co, unsigned char byte)
{
    co->vet[byte]++;
    return co;
}

unsigned long long int *counter_get_vet(tCounter *co)
{
    return co->vet;
}

unsigned long long int counter_get_vetx(tCounter *co, int idx)
{
    assertr(idx >= 0 && idx <= 255, "get_vet_item_counter: out of bounds\n");
    return co->vet[idx];
}

/*void iter_counter(tCounter *co, void (*func)(tCounter *co))
{

}*/

void counter_print(tCounter *co)
{
    int i;
    for (i = 0; i < 256; i++)
        if (co->vet[i] > 0)
            printf("\nCHAR '%c' = %llu", i, co->vet[i]);

    printf("\n");
}