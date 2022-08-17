/**
 * @file rwbin.h
 * @author Felipe M. Barina
 * @author Vitor F. Calmon
 * @brief Functions to ease binary read/write operations in a uniform manner.
 * @date 2022-08-16
 * 
 */
#ifndef RWBIN_H_
#define RWBIN_H_

#include <stdio.h>
#include "bits.h"

/**
 * @brief Write binary file signature block (magic bits).
 * 
 * @param f Binary file stream.
 * @param signature Signature bytes to write.
 * @param size Amount of bytes in signature.
 */
void wbin_magic_block(FILE *f, unsigned char *signature, unsigned char size);

/**
 * @brief Write a short (<=255 characters) string to binary file.
 * 
 * @param f Binary file stream.
 * @param str String of characters to write.
 */
void wbin_short_str_block(FILE *f, char *str);

/**
 * @brief Write a long (<=65535 characters) string to binary file.
 * 
 * @param f Binary file stream.
 * @param str String of characters to write.
 */
void wbin_long_str_block(FILE *f, char *str);

/**
 * @brief Write a block of bits to binary file.
 * 
 * @param f Binary file stream.
 * @param bs Bits from which to write. 
 * @return unsigned int Amount of bytes (containing the bits) written.
 */
unsigned int wbin_bits_block(FILE *f, tBits *bs);

/**
 * @brief Read and check binary file signature block (magic bits).
 * 
 * @param f Binary file stream.
 * @param signature Signature bytes to check against.
 * @param size Amount of bytes in signature.
 * @return int Signature comparison result. 
 * One in case of match success, zero in case of failure.
 */
int rbin_magic_block(FILE *f, unsigned char *signature, unsigned char size);

/**
 * @brief Read a short (<=255 characters) string from binary file.
 * 
 * @param f Binary file stream.
 * @return char* String read.
 */
char *rbin_short_str_block(FILE *f);

/**
 * @brief Read a long (<=65535 characters) string from binary file.
 * 
 * @param f Binary file stream.
 * @return char* String read.
 */
char *rbin_long_str_block(FILE *f);

/**
 * @brief Read a block of bits from binary file.
 * 
 * @param f Binary file stream.
 * @param bs Bits to which write. 
 * @return unsigned int Amount of bytes (containing the bits) read.
 */
unsigned int rbin_bits_block(FILE *f, tBits * bs);

#endif /* RWBIN_H_ */