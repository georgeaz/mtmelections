//
// Created by George on 12/8/2018.
//

#ifndef INC_3011_MAYOR_H
#define INC_3011_MAYOR_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

void* copyInt(void* integer);
void freeInt(void* integer);

bool intEquals(void* integer1, void* integer2);

bool intGreaterThan(void* integer1, void* integer2);

#endif //INC_3011_MAYOR_H
