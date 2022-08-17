/**
 * @file compfile.h
 * @author Felipe M. Barina
 * @author Vitor F. Calmon
 * @brief Manage the data and operations relating to a compressed file.
 * @date 2022-08-16
 * 
 */
#ifndef COMPFILE_H_
#define COMPFILE_H_

#include "tree.h"
#include "bits.h"

typedef struct compfile_st tCompfile;

/**
 * @brief Create a tCompfile.
 * 
 * @return tCompfile* tCompfile.
 */
tCompfile *comp_init();

/**
 * @brief Free a tCompfile and all the memory it has allocated.
 * 
 * @param cf tCompfile.
 */
void comp_free(tCompfile *cf);

/**
 * @brief Write the file header from a tCompfile, including metadata such as the
 * file name, extension and the binary file signature.
 * 
 * @param cf tCompfile.
 */
void comp_write_header(tCompfile *cf);

/**
 * @brief Write file data of a tCompfile in the form of a given block of bits.
 * 
 * @param cf tCompfile.
 * @param bs Bits to write from.
 * @return unsigned int Amount of bytes written.
 */
unsigned int comp_write_data(tCompfile *cf, tBits *bs);

/**
 * @brief Read the file header to a tCompfile, including metadata such as the
 * file name, extension and the binary file signature.
 * 
 * @param cf tCompfile.
 */
void comp_read_header(tCompfile *cf);

/**
 * @brief Write file data of a tCompfile in the form of a block of bits to a 
 * given tBits.
 * 
 * @param cf tCompfile.
 * @param bs Bits to read to.
 * @return unsigned int Amount of bytes read.
 */
unsigned int comp_read_data(tCompfile *cf, tBits *bs);

/**
 * @brief Get path of a tCompfile.
 * 
 * @param cf tCompfile.
 * @return char* File path string.
 */
char *comp_get_path(tCompfile *cf);

/**
 * @brief Set path of a tCompfile.
 * 
 * @param cf tCompfile.
 * @param path File path string.
 */
void comp_set_path(tCompfile *cf, char *path);

/**
 * @brief Get name of a tCompfile.
 * 
 * @param cf tCompfile.
 * @return char* File name.
 */
char *comp_get_name(tCompfile *cf);

/**
 * @brief Set name of a tCompfile.
 * 
 * @param cf tCompfile.
 * @param name File name.
 */
void comp_set_name(tCompfile *cf, char *name);

/**
 * @brief Get extension of a tCompfile.
 * 
 * @param cf tCompfile.
 * @return char* File extension.
 */
char *comp_get_ext(tCompfile *cf);

/**
 * @brief Set extension of a tCompfile.
 * 
 * @param cf tCompfile.
 * @param ext File extension.
 */
void comp_set_ext(tCompfile *cf, char *ext);

/**
 * @brief Get encoding tree of a tCompfile.
 * 
 * @param cf tCompfile.
 * @return tTree* Encoding tree.
 */
tTree *comp_get_tree(tCompfile *cf);

/**
 * @brief Set encoding tree of a tCompfile.
 * 
 * @param cf tCompfile.
 * @param tr Encoding tree.
 */
void comp_set_tree(tCompfile *cf, tTree *tr);

#endif /* COMPFILE_H_ */