#include "tree.h"
#include <stdlib.h>
#include "bits.h"
#include "assertr.h"

#define TREE_SERIAL_BITMAP_SIZE 32768

struct tree_st
{
    unsigned char info;
    unsigned long long int weight;
    tTree *left;
    tTree *right;
};

tTree *tree_init_empty()
{
    return NULL;
}

tTree* tree_init (char c, unsigned long long int weight, tTree* e, tTree* d) 
{
    tTree *tree = (tTree *)malloc(sizeof(tTree));

    tree->info = c;
    tree->weight = weight;
    tree->left = e;
    tree->right = d;
    
    return tree;
}

tTree *tree_free(tTree *tree)
{
    if (!tree_empty(tree))
    {
        tree_free(tree->left);
        tree_free(tree->right);
        free(tree);
    }
    return NULL;
}

int tree_empty(tTree *tree)
{
    return tree == NULL;
}

void tree_print(tTree *tree)
{
    if (!tree_empty(tree))
    {
        if (tree->info)
            printf("|%c: %d", tree->info, (int)tree->info);
        else
            printf("|NULL");

        printf(" W: %lld|\n", tree->weight);
        tree_print(tree->left);
        tree_print(tree->right);
    }
}

char tree_info(tTree *tree)
{
    return tree->info;
}

int tree_is_leaf(tTree *tree)
{
    return ((tree->left == NULL && tree->right == NULL) ? 1 : 0);
}

int tree_weight(tTree *tree)
{
    return tree->weight;
}

static tBits *tree_serialize_(tTree *tree, tBits *bs)
{
    if (tree->left == NULL && tree->right == NULL)
    {
        bits_append(bs, 0x01);
        int i;
        for (i = 0; i < 8; i++)
            bits_append(bs, (tree->info) >> (7 - i));
    }
    else
    {
        bits_append(bs, 0x00);
        tree_serialize_(tree->left, bs);
        tree_serialize_(tree->right, bs);
    }
    return bs;
}

tBits *tree_serialize(tTree *tree)
{
    tBits *bs = bits_init(TREE_SERIAL_BITMAP_SIZE);
    bs = tree_serialize_(tree, bs);
    return bs;
}

tTree *tree_deserialize(tBits *bs)
{
    static unsigned int bs_index = 0;
    unsigned char bit = bits_get_bit(bs, bs_index++);
    tTree *ntr;

    if (bit)
    {
        unsigned char val = 0;
        unsigned int max = bs_index + 8;

        for (; bs_index < max; bs_index++)
        {
            if (max - bs_index != 8)
                val <<= 1;
            val += bits_get_bit(bs, bs_index);
        }

        ntr = tree_init(val, 0, NULL, NULL);
    }
    else
    {
        tTree *nltr = tree_deserialize(bs);
        tTree *nrtr = tree_deserialize(bs);
        ntr = tree_init(0, 0, nltr, nrtr);
    }

    if (bits_get_len(bs) - 1 == bs_index)
        bs_index = 0;

    return ntr;
}

tTree *tree_nav(tTree *tr, unsigned char dir)
{
    assertr(!dir || dir == 1, "Direção de navegação inválida");

    if (dir)
    {
        assertr(tr->right != NULL, "Não pode navegar a dir: NULL");
        return tr->right;
    }
    else
    {
        assertr(tr->left != NULL, "Não pode navegar a left: NULL");
        return tr->left;
    }
}