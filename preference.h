//
// Created by George on 12/1/2018.
//

#ifndef INC_3011_PREFERENCE_H
#define INC_3011_PREFERENCE_H
#include "typedefs_and_general_functions.h"
#include "stdbool.h"
/**PreferenceDestroy: releases the preference candidate id and score, and then
 * releases the preference.
 * */
Preference PreferenceCopy(Preference);
/**PreferenceCopy: Creates a new copy of the preference and returns a copy of it.
 *  returns:
 *              - NULL if a NULL was sent or a memory allocation failed.
 *              - a new copy of preference otherwise.
* */
void PreferenceDestroy(Preference);
/**PreferenceIsEqual: checks if two Preferences are equal, two preferences are
 * determined equal if they have the same candidate id or the same preference
 * score. returns:
 *              - True if the candidate id's are equal.
 *              - True if the scores are equal.
 *              - False otherwise.
* */
bool PreferenceIsEqual(Preference, Preference);
/**PreferenceCompare: checks if the first preference score is greater than the
 * second preference score.
 *  @return
 *      True - if the first score is greater than the second score.
 *      False - otherwise.
* */
bool PreferenceCompare(Preference,Preference);
/**
* PreferenceCreate: Allocates a new empty Preference.
* @return
* 	NULL - if allocations failed.
* 	A new Preference in case of success.
*/
Preference PreferenceCreate();
/**
* PreferenceInsertInformation: Insert the Candidate id and the score to the
 * empty Preference.
* */
void PreferenceInsertInformation(Preference, int, int);
/**
* PreferenceCandidateGetId: returns the preferred candidate id.
* @return
* 	NOT_FOUND(-1) - if the Preference is NULL.
* 	the preferred candidate id otherwise.
*/
int PreferenceCandidateGetId(Preference);

#endif //INC_3011_PREFERENCE_H
