/**
 * @file pathman.h
 * @author Felipe M. Barina
 * @author Vitor F. Calmon
 * @author Rhuan Garcia
 * @brief Path manipulation functions. You should use cwalk instead.
 * @date 2022-08-16
 * 
 */
#ifndef PATHMAN_H_
#define PATHMAN_H_

/**
 * @brief Extend path by adding a string to its end.
 *
 * @param path Pre-allocated path string.
 * @param add String to be added at the end of path.
 * @return char* Path string with extended path.
 */
char *expth(char *path, char *add);

/**
 * @brief Trim path by removing characters from the end up to and including
 * the first directory separator found. If the last character of path is the 
 * directory separator, ignore it and find the previous one.
 *
 * @param path Pre-allocated path string.
 * @return char* Path string with trimmed path.
 */
char *trpth(char *path);

/**
 * @brief Add more to path by adding a string at the end with a directory
 * separator in between. If path ends with a directory separator, skip adding
 * the directory separator.
 *
 * @param path Pre-allocated path string.
 * @param add String to be added at the end of path.
 * @return char* Path string with extended directory separated path.
 */
char *adpth(char *path, char *add);

/**
 * @brief Trim path by removing the file extension at the end. An extension is
 * defined as the characters after the last dot in the given path. The dot is 
 * also removed. If no dot is found, nothing is done.
 * 
 * @param path Pre-allocated path string.
 * @return char* Path string with extension removed.
 */
char *trextpth(char *path);

/**
 * @brief Get extension from the file at the end of path. An extension is
 * defined as the characters after the last dot in the given path. The dot is 
 * not included. If no dot is found, an empty path will be returned.
 * 
 * @param path Pre-allocated path string.
 * @return char* Extension string from path.
 */
char *getextpth(char *path);

/**
 * @brief Get file basename from the file at the end of path. A file name is
 * defined as the characters before the last dot and after the last directory
 * separator in the given path. 
 * 
 * @param path Pre-allocated path string.
 * @return char* File name string from path.
 */
char* getnamepth(char* path);

#endif /* PATHMAN_H_ */
