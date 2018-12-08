//
// Created by George on 11/28/2018.
//
#include <stdbool.h>
#ifndef HOMEWORK2ELECTIONS_CITIZEN_H
#define HOMEWORK2ELECTIONS_CITIZEN_H
#include "set.h"
#include "typedefs_and_general_functions.h"
/**
 * A citizen implementation
 *
 *
 *     * The following functions are available:
 *     CitizenCreate            - Creates a new empty list
 *     CitizenDestroy
 *     GetCitizenInformation    -
 *
 *     */

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

Citizen CitizenCreate();
void CitizenDestroy(Citizen );
Citizen CitizenCopy(Citizen );
Information CitizenGetInformation(Citizen ,CitizenInformation );
Preference CitizenFindPrefernce(Citizen,int);

int CitizenCompare(Citizen ,Citizen );
void CitizenRemovePreferences(Citizen);
int CitizenGetid(Citizen citizen);
CitizenResult CitizenRemovePrefrence(Citizen,int);
void CitizenCandidateToBeRemovePrefrences(Citizen );
bool CitizenCandidateAlreadySupported(City,Citizen,int candidate_id,int priority);
bool CitizenSupportCandidate(Citizen,int candidate_id,int priority);
void CitizenInsertInformation(Citizen ,int id,const String name,int education_years,int age);
void PrintCitizen(Citizen citizen);
Preference CitizenGetPreferredCandidate(Citizen );
#endif //HOMEWORK2ELECTIONS_CITIZEN_H
