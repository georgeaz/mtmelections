
#include "mayor.h"
void* copyInt(void* integer){
    int* newInt = malloc(sizeof(*newInt));
    if(!newInt){
        return NULL;
    }
    *newInt = *((int*)integer);
    return newInt;
}

void freeInt(void* integer){
    free(integer);
}

bool intEquals(void* integer1, void* integer2){
    return *((int*)integer1) == *((int*)integer2);
}

bool intGreaterThan(void* integer1, void* integer2){
    return 0;
}
