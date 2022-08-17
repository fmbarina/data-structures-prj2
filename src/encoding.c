#include "encoding.h"
#include "tree.h"
#include "bits.h"
#include "bytes.h"
#include "assertr.h"

#define ENC_MAX_IN 4096 /* bytes*/
#define ENC_MAX_OUT 65535 /* bits*/
#define DEC_MAX_IN 4096 /* bits */
#define DEC_MAX_OUT 65535 /* bytes*/

/* How many exceeding bytes are tolerated */
#define ENC_TOL 0 
/* How many exceeding bits are tolerated */
#define DEC_TOL 256

/* função auxiliar que preenche um tBits pré criado com bits de
 * caminho até alcançar o byte (unsigned char) b na árvore. Note
 * que o tBits é retornado com o caminho ao contrário: o 1° bit
 * está em tBits[length - 1]
 */
static int bitpath_to_byte(tBits* bs, tTree* tr, unsigned char b)
{
    if (tree_is_leaf(tr))
    {
        unsigned char byte_ret = tree_info(tr);
        if (byte_ret == b)
            return 1;
        else
            return 0;
    }
    
    /* Left */
    if (bitpath_to_byte(bs, tree_nav(tr, 0), b))
    {
        bits_append(bs, 0x00);
        return 1;
    }
    
    /* Right */
    if (bitpath_to_byte(bs, tree_nav(tr, 1), b))
    {
        bits_append(bs, 0x01);
        return 1;
    }
    
    return 0;
}

/* TODO: Maybe in the future, consider a more efficient way to do this.
 * Currently, it's necessary to search the tree for every byte. Maybe 
 * build a hash table for all bytes the first time, then use that as a
 * translation dictionary later?
 */
tBits *encode(tTree *tr, tBytes *bt, tBits* bs)
{
    assertr(bytes_get_len(bt) <= ENC_MAX_IN + ENC_TOL, "tBytes demais");

    unsigned int i;
    for (i = 0; i < bytes_get_len(bt); i++)
    {
        /* Get bit by bit path to byte in tree */
        tBits* encoded = bits_init(256);
        bitpath_to_byte(encoded, tr, bytes_get_byte(bt, i));
        
        int j;
        for (j = bits_get_len(encoded) - 1; j >= 0; j--)
            bits_append(bs, bits_get_bit(encoded, j));

        bits_free(encoded);
    }

    return bs;
}

unsigned int encode_limit_in()
{
    return (unsigned int)ENC_MAX_IN;
}

unsigned int encode_limit_out()
{
    return (unsigned int)ENC_MAX_OUT;
}

/* Navegar arvore seguindo a direção dos tBits
 * (0: esquerda, 1: direita) até atingir uma folha. Ao
 * achar a folha, adicionar o byte nela contido ao tBytes
 * de retorno.
 */
tBytes* decode(tTree* tr, tBytes *bt, tBits* bs)
{
    assertr(bits_get_len(bs) <= DEC_MAX_IN + DEC_TOL, "tBits demais");

    tTree *aux_tr = tr;

    unsigned int steps = 0;
    while (bits_cur(bs) < bits_get_len(bs))
    {
        unsigned char dir = bits_read(bs); steps++;
        aux_tr = tree_nav(aux_tr, dir);

        if (tree_is_leaf(aux_tr))
        {
            bytes_append(bt, tree_info(aux_tr));
            aux_tr = tr;
            steps = 0;
        }
    }

    if (steps)
        bits_offset_cur(bs, (-steps));

    return bt;
}

unsigned int decode_limit_in()
{
    return (unsigned int)DEC_MAX_IN;
}

unsigned int decode_limit_out()
{
    return (unsigned int)DEC_MAX_OUT;
}