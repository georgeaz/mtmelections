//
// Created by George on 11/30/2018.
//
#include <stdlib.h>
#include "typedefs_and_general_functions.h"
//check when u pass agruments that they are not pointers

//the Name shit should be a char*
void StringCopy(const String source_string,String destination){
    //String new_copy=(String)malloc(sizeof(String*)*Stringlength(source_string));
   // if(new_copy==NULL){
    //    return NULL;
 //   }
    int i=0;
    for(;source_string[i] !='\0';i++){
        destination[i]=source_string[i];
    }
    destination[i]='\0';
    //return new_copy;

}
size_t Stringlength(const String  string)
{
     String ptr;

    for (ptr = string; *ptr; ++ptr)
        ;
    //LAST BIT WERE ADDED
    return (ptr - string)+LAST_BIT;
}
void StringCopyDestroy(String string){
    free(string);
}