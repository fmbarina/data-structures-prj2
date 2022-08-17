/**
 * @file encoding.h
 * @author Felipe M. Barina
 * @author Vitor F. Calmon
 * @brief Encode and decode binary data with an encoding tree.
 * @date 2022-08-16
 * 
 */
#ifndef ENCODING_H_
#define ENCODING_H_

#include "tree.h"
#include "bits.h"
#include "bytes.h"

/**
 * @brief Encode bytes to compressed bits, using an encoding tree.
 * 
 * @param tr Encoding tree.
 * @param bt Bytes to encode.
 * @param bs Bits to fill.
 * @return tBits* 
 */
tBits *encode(tTree *tr, tBytes *bt, tBits* bs);

/**
 * @brief Get limit of bytes to encode.
 * 
 * @return unsigned int Limit.
 */
unsigned int encode_limit_in();

/**
 * @brief Get maximum output of bits after encoding.
 * 
 * @return unsigned int Limit.
 */
unsigned int encode_limit_out();

/**
 * @brief Decode bits to uncompressed Bytes, using an encoding tree.
 * 
 * @param tr Encoding tree.
 * @param bt Bytes to fill.
 * @param bs Bits to decode.
 * @return tBytes* 
 */
tBytes* decode(tTree* tr, tBytes *bt, tBits* bs);

/**
 * @brief Get limit of bits to decode.
 * 
 * @return unsigned int Limit.
 */
unsigned int decode_limit_in();

/**
 * @brief Get maximum output of bytes after decoding.
 * 
 * @return unsigned int Limit.
 */
unsigned int decode_limit_out();

#endif /* ENCODE_H_ */