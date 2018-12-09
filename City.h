//
// Created by User on 28/11/2018.
// Created by Lina Bshouty القمر

#ifndef UNTITLED1_CITY_H
#define UNTITLED1_CITY_H


#include "citizen.h"
#include "Candidate.h"
#include "Vote.h"
#include "preference.h"
#include "uniqueOrderedList/uniqueOrderedList.h"

typedef enum CityResult_t{
    CITY_MEMORY_ERROR,
    CITY_NULL_ARGUMENT,
    CITY_ALREADY_EXISTS,
    CITY_NOT_SAME_CITY,//maybe we wont use this
    CITY_DOES_NOT_EXIST,
    CITY_SUCCESS,
    CITY_CANDIDATE_DOES_NOT_EXIST,
    CITY_NOT_THE_SAME_CITY,
    CITY_CITIZEN_PRIORITY_EXISTS,
    CITY_CANDIDATE_ALREADY_SUPPORTED,
    CITY_CITIZEN_CAN_NOT_SUPPORT,
  CITY_NO_CANDIDATES_IN_CITY
}CityResult;
//void CityPrint(City );
int CityGetId(City);
Set CityGetCitizens(City );
Set CityGetCandidates(City );
//124:changed from Name to String
String CityGetName(City);
void CityDestroy(City);
City CityCreate();
City CityCopy(City);
int CityCompare(City ,City );
bool CityIsLegal(City );
bool CityIsCandidate(City,int );
CityResult  CitySupportCandidate(City,Citizen,int candidate_id,int priority);
Citizen CityGetCitizen(City ,int );
CitizenResult CityInsertCitizen(City ,const String citizen_name, int citizen_id,
                                 int citizen_age, int education_years);
CandidateResult CityInsertCandidate(City, int);
CandidateResult CityRemoveCandidate(City,Candidate);
void CityInsertInformation(City, const String, int);
void CityCitizenRemovePrefrence(City,int candidate_id);
CityResult CityMayorOfCity(City city,Id mayor);
CitizenResult CityRemoveCitizen(City city, Citizen citizen);
Vote CityGetCandidateVote(UniqueOrderedList, int candidate_id);
CityResult CityUpdateCandidateVotes(UniqueOrderedList ,Vote new_vote, Vote
old_vote);
#endif //UNTITLED1_CITY_H
