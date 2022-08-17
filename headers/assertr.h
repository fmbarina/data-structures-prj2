/**
 * @file assertr.h
 * @author Felipe M. Barina
 * @author Vitor F. Calmon
 * @brief Custom assert function with error message.
 * @date 2022-08-16
 * 
 */
#ifndef ASSERTR_H_
#define ASSERTR_H_

/**
 * @brief Assert that condition is true. If false, print error message 
 * and quit the program.
 * 
 * @param cond Condition to assert is true.
 * @param err Error message to print if condition is false.
 */

void assertr(int cond, char *err);

#endif /* ASSERTERR_H_ */