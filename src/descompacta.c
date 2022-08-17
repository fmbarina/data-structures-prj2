/**
 * @file descompacta.c
 * @author Felipe M. Barina
 * @author Vitor F. Calmon
 * @brief Program to decompress files compressed with 'compacta'
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
#include "bytes.h"
#include "bits.h"

int main(int argc, char *argv[])
{
    /* Lacking input argument guard */
    if (argc < 2)
    {
        printf("Argumentos insuficientes, verifique se passou o arquivo.");
        exit(1);
    }

    /* Instantiate file types */
    tCompfile *input = comp_init();
    tReglfile *output = regl_init();

    comp_set_path(input, argv[1]);

    /* Read and assign compacted file metadata */
    comp_read_header(input);
    regl_set_name(output, comp_get_name(input));
    regl_set_ext(output, comp_get_ext(input));

    char *outpath = strdup(regl_get_name(output)); 
    outpath = expth(expth(outpath, "."), regl_get_ext(output));
    regl_set_path(output, outpath);
    free(outpath);

    /* TODO: unsigned int dec_lim_in = decode_limit_in();*/

    unsigned int dec_lim_out = decode_limit_out();

    tBits* leftovers = bits_init(256);

    /* Decompact and write file contents */
    while (1)
    {
        tBits *read_buf = bits_init(4120);
        /* tBits *read_buf = bits_init(dec_lim_in); */
        tBytes *write_buf = bytes_init(dec_lim_out);

        /* If there's any leftovers, insert them in the
         * read buffer to be decoded next 
         */
        if(bits_get_len(leftovers))
        {
            for (; bits_cur(leftovers) < bits_get_len(leftovers);)
                bits_append(read_buf, bits_read(leftovers));
            
            bits_free(leftovers);
            leftovers = bits_init(256);
        }   

        /* Read bits from input file, save the return in r_ret */
        unsigned int r_ret = comp_read_data(input, read_buf);
        
        /* If there are no bits (file has ended or can't be read), stop */
        if(!r_ret)
        {
            bytes_free(write_buf);
            bits_free(read_buf);
            break;
        }

        /* Get decoded bytes with the read bits using the encoding tree */
        decode(comp_get_tree(input), write_buf, read_buf);

        /* Check if there's any bits in read_buf not decoded yet.
         * If so, add them to the leftovers to be decoded next time.
         * This happens because continuous bits may be separated in
         * the compacting process.
         */
        if(bits_cur(read_buf) != bits_get_len(read_buf))
            for (; bits_cur(read_buf) < bits_get_len(read_buf);)
                bits_append(leftovers, bits_read(read_buf));

        /* Write the decoded bytes to the output file */
        regl_write_bytes(output, write_buf);

        bits_free(read_buf);
        bytes_free(write_buf);
    }

    /* Free memory and close files */
    bits_free(leftovers);
    comp_free(input);
    regl_free(output);

    return 0;
}