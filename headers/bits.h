/**
 * @file bits.h
 * @author Felipe M. Barina
 * @author Vitor F. Calmon
 * @brief Manage a collection of bits.
 * @date 2022-08-16
 * 
 */
#ifndef BITS_H_
#define BITS_H_

typedef struct bits_st tBits;

/**
 * @brief Create tBits.
 * 
 * @param max_length Max number of bits in tBits.
 * @return tBits* tBits. 
 */
tBits *bits_init(unsigned int max_length);

/**
 * @brief Free a tBits and all the memory it has allocated.
 * 
 * @param bs tBits.
 */
void bits_free(tBits *bs);

/**
 * @brief Append a bit to a tBits.
 * 
 * @param bs tBits.
 * @param bit Bit value to append. Must be zero or one.
 */
void bits_append(tBits *bs, unsigned char bit);

/**
 * @brief Reads bits, bit by bit, from a tBits. A cursor inside 
 * advances one bit every function call. Attempting to read past
 * the amount of bits in tBits will result in an error.
 * 
 * @param bs tBits.
 * @return unsigned char Bit read.
 */
unsigned char bits_read(tBits *bs);

/**
 * @brief Set a bit in a tBits.
 * 
 * @param bs tBits.
 * @param idx Index of bit to set. Must be under tBits length.
 * @param bit Bit value to set. Must be zero or one.
 */
void bits_set_bit(tBits *bs, unsigned int idx, unsigned char bit);

/**
 * @brief Get a bit in a tBits.
 * 
 * @param bs tBits.
 * @param idx Index of bit to set. Must be under tBits length.
 * @return unsigned char Bit value, one or zero.
 */
unsigned char bits_get_bit(tBits *bs, unsigned int idx);

/**
 * @brief Set length of a tBits manually.
 * 
 * @param bs tBits.
 * @param len Value of length to set.
 */
void bits_set_len(tBits* bs, unsigned int len);

/**
 * @brief Get current length of a tBits.
 * 
 * @param bs tBits.
 * @return unsigned int Current length.
 */
unsigned int bits_get_len(tBits *bs);

/**
 * @brief Set cursor of a tBits manually.
 * 
 * @param bs tBits.
 * @param cur Value of length to set. Must be under tBits length.
 */
void bits_set_cur(tBits *bs, unsigned int cur);

/**
 * @brief Offset cursor of a tBits manually.
 * 
 * @param bs tBits.
 * @param offset Number to offset cursor by.
 */
void bits_offset_cur(tBits *bs, unsigned int offset);

/**
 * @brief Get current length of a tBits.
 * 
 * @param bs tBits.
 * @return unsigned int Current tBits cursor.
 */
unsigned int bits_cur(tBits *bs);

/**
 * @brief Get maximum length of a tBits.
 * 
 * @param bs tBits.
 * @return unsigned int Maximum tBits.
 */
unsigned int bits_max(tBits *bs);

/**
 * @brief Get a tBits bits vector.
 * 
 * @param bs tBits.
 * @return unsigned char* Bits vector.
 */
unsigned char *bits_contents(tBits *bs);

/**
 * @brief Print current bits in a tBits.
 * 
 * @param bs tBits.
 */
void bits_print(tBits *bs);

#endif /* BITS_H_ */