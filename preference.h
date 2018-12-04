//
// Created by George on 12/1/2018.
//

#ifndef INC_3011_PREFERENCE_H
#define INC_3011_PREFERENCE_H
#include "typedefs_and_general_functions.h"
#include "stdbool.h"


bool PreferenceCompare(Vote,Vote);
bool PreferenceIsEquals(Vote,Vote);
Vote PreferenceCopy(Vote);
void PreferenceDestroy(Vote);
void PreferenceChangeInformation(Vote,int,int);
Vote PreferenceCreate();
int PreferenceGetId(Vote);


#endif //INC_3011_PREFERENCE_H
