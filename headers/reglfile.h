/**
 * @file reglfile.h
 * @author Felipe M. Barina
 * @author Vitor F. Calmon
 * @brief Manage the data and operations relating to a regular file.
 * @date 2022-08-16
 * 
 */
#ifndef REGLFILE_H_
#define REGLFILE_H_

#include "bytes.h"

typedef struct reglfile_st tReglfile;

/**
 * @brief Create a tReglfile.
 * 
 * @return tReglfile* tReglfile.
 */
tReglfile* regl_init();

/**
 * @brief Free a tReglfile and all the memory it has allocated.
 * 
 * @param rf tReglfile.
 */
void regl_free(tReglfile* rf);

/**
 * @brief Read bytes from a tReglfile to given tBytes.
 * 
 * @param rf tReglfile.
 * @param bt Bytes to read to.
 * @return unsigned int Amount of bytes read.
 */
unsigned int regl_read_bytes(tReglfile* rf, tBytes* bt);

/**
 * @brief Write bytes to a tReglfile from given tBytes.
 * 
 * @param rf tReglfile.
 * @param bt Bytes to write from.
 * @return unsigned int Amount of bytes written.
 */
unsigned int regl_write_bytes(tReglfile* rf, tBytes* bt);

/**
 * @brief Read a single byte from a tReglfile to a single byte pointer.
 * 
 * @param rf tReglfile.
 * @param byte Byte pointer to read to.
 * @return int Read operation result. 
 * One in case of read success, zero in case of failure.
 */
int regl_read_single_byte(tReglfile *rf, unsigned char * byte);

/**
 * @brief Reset the tReglfile cursor to the beggining of the file.
 * 
 * @param rf tReglfile.
 */
void regl_reset_cursor(tReglfile* rf);

/**
 * @brief Get path of a tReglfile.
 * 
 * @param rf tReglfile.
 * @return char* File path.
 */
char* regl_get_path(tReglfile *rf);

/**
 * @brief Set path of a tReglfile.
 * 
 * @param rf tReglfile.
 * @param path File path.
 */
void regl_set_path(tReglfile *rf, char* path);

/**
 * @brief Get name of a tReglfile.
 * 
 * @param rf tReglfile.
 * @return char* File name.
 */
char *regl_get_name(tReglfile *rf);

/**
 * @brief Set name of a tReglfile.
 * 
 * @param rf tReglfile.
 * @param name File name.
 */
void regl_set_name(tReglfile* rf, char* name);

/**
 * @brief Get extension of a tReglfile.
 * 
 * @param rf tReglfile.
 * @return char* File extension.
 */
char *regl_get_ext(tReglfile *rf);

/**
 * @brief Set extension of a tReglfile.
 * 
 * @param rf tReglfile.
 * @param ext File extension.
 */
void regl_set_ext(tReglfile* rf, char* ext);

/**
 * @brief Attempt to extract and set the tReglfile name and extension from 
 * its path. tReglfile name needs to be set first, else it will result in an 
 * error.
 * 
 * @param rf tReglfile.
 */
void regl_guess_name_ext(tReglfile* rf);

#endif /* REGLFILE_H_ */