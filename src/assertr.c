#include "assertr.h"
#include <stdio.h>
#include <stdlib.h>

/* "Inspired" by bitmap.c, Joao Paulo A. A. */
void assertr(int cond, char *err)
{
    if (!cond)
    {
        printf("\nE: %s\n", err);
        exit(EXIT_FAILURE);
    }
}