//
// Created by George on 12/8/2018.
//

#ifndef INC_3011_MAYOR_H
#define INC_3011_MAYOR_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
/**
* copyInt: Creates a copy of a new integer.
*
* @param integer - Target Integer.
* @return
* 	new integer in case of success.
* 	NULL - otherwise
*/
void* copyInt(void* integer);
/**
* freeInt: Deallocates an integer.
*
* @param integer - Target Integer to destroy.
*/
void freeInt(void* integer);
/**intEquals: checks if the integers are equal.
 *  @return
 *      true - if the integers are equal
 *      false- otherwise.
* */
bool intEquals(void* integer1, void* integer2);
/**intGreaterThan: checks if the first integer is bigger than the second .
 *  @return
 *      true - if the first integer is bigger than the second
 *      false- otherwise.
* */
bool intGreaterThan(void* integer1, void* integer2);

#endif //INC_3011_MAYOR_H
