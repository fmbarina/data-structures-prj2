/**
 * @file bytes.h
 * @author Felipe M. Barina
 * @author Vitor F. Calmon
 * @brief Manage a collection of bytes.
 * @date 2022-08-16
 * 
 */
#ifndef BYTES_H_
#define BYTES_H_

typedef struct bytes_st tBytes;

/**
 * @brief Create tBytes.
 * 
 * @param max_length Max number of bytes in tBytes.
 * @return tBytes* tBytes.
 */
tBytes *bytes_init(unsigned int max_length);

/**
 * @brief Free a tBytes and all the memory it has allocated.
 * 
 * @param bt tBytes.
 */
void bytes_free(tBytes *bt);

/**
 * @brief Append a bytes to a tBytes.
 * 
 * @param bt tBytes.
 * @param byte Byte value to append.
 */
void bytes_append(tBytes *bt, unsigned char byte);

/**
 * @brief Reads bytes, byte by byte, from a tBytes. A cursor inside  
 * advances one byte every function call. Attempting to read past
 * the amount of bytes in tBytes will result in an error.
 * 
 * @param bt tBytes.
 * @return unsigned char Byte read.
 */
unsigned char bytes_read(tBytes *bt);

/**
 * @brief Set a byte in a tBytes.
 * 
 * @param bt tBytes.
 * @param idx Index of byte to set. Must be under tBytes length.
 * @param byte Byte value to set.
 */
void bytes_set_byte(tBytes *bt, unsigned int idx, unsigned char byte);

/**
 * @brief Get a byte in a tBytes.
 * 
 * @param bt tBytes.
 * @param idx Index of byte to set. Must be under tBytes length.
 * @return unsigned char Byte value.
 */
unsigned char bytes_get_byte(tBytes *bt, unsigned int idx);

/**
 * @brief Set length of a tBytes manually.
 * 
 * @param bt tBytes.
 * @param len Value of length to set.
 */
void bytes_set_len(tBytes *bt, unsigned int len);

/**
 * @brief Get current length of a tBytes.
 * 
 * @param bt tBytes.
 * @return unsigned int Current length.
 */
unsigned int bytes_get_len(tBytes *bt);

/**
 * @brief Get maximum length of a tBytes.
 * 
 * @param bt tBytes.
 * @return unsigned int Maximum length.
 */
unsigned int bytes_max(tBytes *bt);

/**
 * @brief Get a tBytes bytes vector.
 * 
 * @param bt tBytes.
 * @return unsigned char* Bytes vector.
 */
unsigned char *bytes_contents(tBytes *bt);

/**
 * @brief Print current bytes in a tBytes.
 * 
 * @param bt tBytes.
 */
void bytes_print(tBytes *bt);

#endif /* BYTES_H_ */