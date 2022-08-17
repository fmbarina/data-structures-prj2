/**
 * @file compacta.c
 * @author Felipe M. Barina
 * @author Vitor F. Calmon
 * @brief Program to compress files to be decompressed with 'descompacta'
 * @date 2022-08-16
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compfile.h"
#include "reglfile.h"
#include "pathman.h"
#include "encoding.h"
#include "tree.h"
#include "treelist.h"
#include "bytes.h"
#include "bits.h"
#include "counter.h"

#define EXT_COMP ".comp\0"

int main(int argc, char *argv[])
{
    /* Lacking input argument guard */
    if (argc < 2)
    {
        printf("Argumentos insuficientes, verifique se passou o arquivo.");
        exit(1);
    }

    /* Instantiate file types */
    tReglfile *input = regl_init();
    tCompfile *output = comp_init();

    regl_set_path(input, argv[1]);
    regl_guess_name_ext(input);
    char *outpath = expth(trextpth(strdup(regl_get_path(input))), EXT_COMP);
    comp_set_path(output, outpath);
    free(outpath);

    /* Compute the byte frequency within the file */
    tCounter *bytes_freq_count = counter_init();
    unsigned char c_byte;
    while (regl_read_single_byte(input, &c_byte) == 1)
        counter_byte_inc(bytes_freq_count, (unsigned char)c_byte);

    regl_reset_cursor(input);

    /* Create tree list from frequency counter */
    int i;
    tTreeList *tree_list = tree_list_inic();
    for (i = 0; i < 256; i++)
    {
        unsigned long long int freq = counter_get_vetx(bytes_freq_count, i);
        if (freq == 0)
            continue;
        tree_list_insert(tree_list, tree_init(i, freq, NULL, NULL));
    }

    /* Create optimized tree from tree_list */
    tTree *optimized_tree = huffman_algorithm(tree_list);

    /* Prepare compacted file data for writing */
    comp_set_name(output, regl_get_name(input));
    comp_set_ext(output, regl_get_ext(input));
    comp_set_tree(output, optimized_tree);

    /* Write compacted file metadata */
    comp_write_header(output);

    /* Max num. of bytes we can decode at a time */
    unsigned int enc_lim_in = encode_limit_in();
    
    /* Max num. of bits we can expect out of decoding */
    unsigned int enc_lim_out = encode_limit_out();
    
    /* Max num. of bits we can write to the compacted file at a time */
    unsigned int dec_lim_in = decode_limit_in();
    
    /* Compress and write file contents */
    while (1)
    {
        tBytes *read_buf = bytes_init(enc_lim_in);
        tBits *encode_buf = bits_init(enc_lim_out);

        /* Read up to numBytes from input file, save the return in r_ret */
        unsigned int r_ret = regl_read_bytes(input, read_buf);

        /* If there are no bytes (file has ended or can't be read), stop */
        if(!r_ret)
        {
            bytes_free(read_buf);
            bits_free(encode_buf);
            break;
        }

        /* Get encoded tBits with the read bytes using the encoding tree */
        encode(comp_get_tree(output), read_buf, encode_buf);

        /* Due to size constraints when decompacting the file later, we should 
         * avoid trying to write too many bits at once to the compacted file. 
         * Instead, we will divide the encoded buffer in batches of size 
         * 'dec_lim_in' and write them, one batch at a time.
         */
        unsigned int encode_len = bits_get_len(encode_buf);
        unsigned int nsets = ((encode_len - 1) / dec_lim_in);
        unsigned int batch;
        for (batch = 0; batch <= nsets; batch++)
        {
            tBits *write_buf = bits_init(dec_lim_in);

            /* Fill write buffer with bits from the set */
            unsigned int nbits = (batch == nsets) ? (encode_len % dec_lim_in) : (dec_lim_in);
            unsigned int bit;
            for (bit = 0; bit < nbits; bit++)
            {
                unsigned int index = (batch * dec_lim_in) + bit;
                bits_append(write_buf, bits_get_bit(encode_buf, index));
            }
            
            /* Send the buffer to be written */
            comp_write_data(output, write_buf);
            
            /* Reset the buffer to start the next set */
            bits_free(write_buf);
        }

        /* Free the buffers to start the next loop clear */
        bytes_free(read_buf);
        bits_free(encode_buf);
    }

    /* Free memory and close files */
    counter_free(bytes_freq_count);
    tree_list_free(tree_list);
    regl_free(input);
    comp_free(output);

    return 0;
}