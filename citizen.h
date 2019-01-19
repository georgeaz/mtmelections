//
// Created by George on 11/28/2018.
//
#include <stdbool.h>
#ifndef HOMEWORK2ELECTIONS_CITIZEN_H
#define HOMEWORK2ELECTIONS_CITIZEN_H
#include "set.h"
#include "typedefs_and_general_functions.h"
#include "mtm_uol/uniqueOrderedList.h"

typedef enum CitizenResult_t{
    CITIZEN_MEMORY_ERROR,
    CITIZEN_NULL_ARGUMENT,
    CITIZEN_ALREADY_EXISTS,
    CITIZEN_DOES_NOT_EXIST,
    CITIZEN_SUCCESS,
    CITIZEN_CANDIDATE_ALREADY_SIPPORETED,
    CITIZEN_DOES_NOT_SUPPORT_CANDIDATE
}CitizenResult;

typedef enum CitizenInformation_t{
  CITIZEN_ID,
  CITIZEN_NAME,
  CITIZEN_EDUCATION_YEARS,
  CITIZEN_AGE,
  CITIZEN_CITY_ID
}CitizenInformation;
/**
* CitizenCreate: Allocates a new empty citizen.
* @return
* 	NULL - if allocations failed.
* 	A new Citizen in case of success.
*/
Citizen CitizenCreate();
/**
* CitizenDestroy: Deallocates an existing citizen. Clears all elements.
*
* @param citizen - Target citizen to be deallocated.
 * If citizen is NULL nothing will be done
*
*/
void CitizenDestroy(Citizen );
/**
* CitizenDestroy: Creates a copy of target citizen.
*
* @param citizen - Target citizen.
* @return
* 	NULL if a NULL was sent or a memory allocation failed.
* 	A citizen containing the same elements as citizen otherwise.
*/
Citizen CitizenCopy(Citizen );
/**
*	CitizenGetInformation: returns a pointer to the desired CitizenInformation
*		for citizen.
* @param citizen - The citizen for which to get information from
* @param CitizenInformation - An enum that targets the element pointer that
 * will be returned.
* @return
* 	A pointer for the desired element of citizen based on CitizenInformation
* 	NULL - if citizen is NULL
*/
Information CitizenGetInformation(Citizen ,CitizenInformation );
/**
*	CitizenFindPrefernce: Searches in the citizen preferences and returns a
 *	pointer to the sent candidate id preferences.
*
* @param citizen - The citizen for which to search in his preferences.
* @param candidate_id - the candidate id to which search for in the citizen
 * preferences.
* @return
* 	A pointer for the preference.
* 	NULL - if citizen is NULL or the citizen does not preffere the candidate.
*/
Preference CitizenFindPrefernce(Citizen,int);
/**CitizenCompare: checks if the citizen id's are equal.
 *  @return
 *      0 - if the citizen id's are equal.
 *      negative or positive int - otherwise.
* */
int CitizenCompare(Citizen ,Citizen );
/**
*	CitizenGetId: returns the Id of target citizen
*
* @param citizen - The citizen for which to get id from.
* @return
* 	the citizen id
* 	-1 - if citizen is NULL
*/
int CitizenGetId(Citizen citizen);
/**
* 	CitizenRemovePrefrence: Removes a preference from the citizen preferences.
* @param citizen - The citizen to remove preference from his preferences.
* @param candidate id - the candidate id in order to find the to remove preference.
* @return
* 	CITIZEN_DOES_NOT_SUPPORT_CANDIDATE if the citizen does not prefere the candidate.
* 	CITIZEN_SUCCESS if the preference were successfully deallocated and removed.
*/
CitizenResult CitizenRemovePrefrence(Citizen,int);
/**
* 	CitizenCandidateToBeRemovePrefrences: Removes future candidate preferences.
 * 	@param citizen - future candidate.
*/
void CitizenCandidateToBeRemovePrefrences(Citizen );
/**
* 	CitizenIsCandidateAlreadySupported: checks if candidate is already supported.
* @param citizen - The citizen to remove preference from his preferences.
* @param candidate id - the candidate id in order to find the to remove preference.
* @return
* 	true -  if the citizen supports the cnadidate.
* 	false - otherwise
 */
bool CitizenIsCandidateSupported(City city, Citizen citizen, int candidate_id);
/**
* 	CitizenSupportCandidate: adds a preference to the citizen preference.
* @param citizen - The citizen to his preferences.
* @param candidate id - the candidate id for the supported candidate.
* @param priority - The priority of the candidate preference.
* @return
* 	true -  the preference were successfully added.
* 	false - the citizen already support the candidate
 * 	or the citizen supports other candidate with the same priority.
 */
bool CitizenSupportCandidate(Citizen,int candidate_id,int priority);
/**
* 	CitizenInsertInformation: adds citizen information to the new allocated citizen.
* @param id -
* @param name -
* @param education_years -
* @param age -
*               All of the above params are the new allocated citizen information.
* @param citizen -  the new allocated citizen
* @return
 */
void CitizenInsertInformation(Citizen ,int id,const String name,int education_years,int age);
/**
* 	CitizenGetPreferredCandidate: returns the most preferred candidate.
* @param citizen - the citizen to return his most preferred candidate.
* @return prefernce - the preference which contains the candidate id and priority,
 *          NULL - if the citizen preferres no one
 */
Preference CitizenGetPreferredCandidate(Citizen );
#endif //HOMEWORK2ELECTIONS_CITIZEN_H
