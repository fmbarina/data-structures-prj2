/**
 * @file counter.h
 * @author Felipe M. Barina
 * @author Vitor F. Calmon
 * @brief Count occurrences of bytes.
 * @date 2022-08-16
 * 
 */
#ifndef COUNTER_H_
#define COUNTER_H_

typedef struct counter_st tCounter;

/**
 * @brief Create a Byte counter.
 * 
 * @return tCounter* Byte counter.
 */
tCounter *counter_init();

/**
 * @brief Increment the count of a byte in a byte counter.
 * 
 * @param co Byte counter.
 * @param byte Byte to increment the count of.
 * @return tCounter* Current byte count for the given byte.
 */
void *counter_byte_inc(tCounter *co, unsigned char byte);

/**
 * @brief Free byte counter and all the memory it has allocated.
 * 
 * @param co Byte counter.
 */
void counter_free(tCounter *co);

/**
 * @brief Get the vector of byte occurrences used by a counter.
 * 
 * @param co Byte counter.
 * @return unsigned long long int* Byte count vector.
 */
unsigned long long int *counter_get_vet(tCounter *co);

/**
 * @brief Get the count of a byte in a byte counter.
 * 
 * @param co Byte counter.
 * @param idx Byte to get occurrences of, int for better use in loops.
 * @return unsigned long long int Byte count.
 */
unsigned long long int counter_get_vetx(tCounter *co, int idx);

/* void iter_counter(tCounter *co, void (*func)(tCounter *co)); */

/**
 * @brief Print the current count of all bytes in a byte counter.
 * 
 * @param co Byte counter.
 */
void counter_print(tCounter* co);

#endif /* COUNTER_H_ */