//
// Created by User on 28/11/2018.
//

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "City.h"
struct City_t{
    Id id;
    String name;
    Set citizens;
    Set candidates;

};
void CityPrint(City city){

    printf("People Of:%s\n",city->name);
    printf("ID:%d\n",*city->id);
    printf("======================\n");
    Citizen citizen=setGetFirst(city->citizens);
    while(citizen){
        PrintCitizen(citizen);
      citizen= setGetNext(city->citizens);
    }
}

int CityGetId(City city){
    return *(city->id);
}
String CityGetName(City city){
    return  city->name;
}
void CityDestroy(City city){
    free(city->name);
    free(city->id);
    setDestroy(city->citizens);
    free(city);
}
City CityCreate(){
    City city=(City)malloc(sizeof(*city));
    Set citizens=setCreate((copySetElements)CitizenCopy,(freeSetElements)CitizenDestroy,(compareSetElements)CitizenCompare);
    Set candidates=setCreate((copySetElements)CandidateCopy,(freeSetElements)CandidateDestroy,(compareSetElements)CandidateCompare);

    Id id=(Id)malloc(sizeof(*id));
    if(city==NULL||citizens==NULL||id==NULL||candidates==NULL){
        free(city);
        setDestroy(citizens);
        setDestroy(candidates);
        free(id);
        return NULL;
    }
    city->id=id;
    city->citizens=citizens;
    city->candidates=candidates;
    return city;
}
City CityCopy(City source_city){
    //if were added
    City new_city= CityCreate();
    if(source_city==NULL||new_city==NULL)
        return NULL;
    //setCopy were added, we have to malloc for a new copy..
    new_city->citizens=setCopy(source_city->citizens);
    new_city->name=(String)malloc(sizeof(String*)*Stringlength(source_city->name));
    StringCopy(source_city->name,new_city->name);
    if(new_city->name==NULL||new_city->citizens==NULL){
        CityDestroy(new_city);
        return NULL;
    }
    new_city->id=source_city->id;
        return new_city;
}
CitizenResult CityInsertCitizen(City city,const String citizen_name,
        int citizen_id, int citizen_age, int education_years){
    //lkjk
        //the whole function were replaced
        Citizen new_citizen=CitizenCreate();
        if(new_citizen==NULL)return CITIZEN_MEMORY_ERROR;
        CitizenInsertInformation(new_citizen,citizen_id,citizen_name,
                education_years,citizen_age);
    SetResult result=setAdd(city->citizens,new_citizen);
    switch(result){
        case SET_NULL_ARGUMENT:
            return CITIZEN_NULL_ARGUMENT;
        case SET_OUT_OF_MEMORY:
            return CITIZEN_MEMORY_ERROR;
        case SET_ITEM_ALREADY_EXISTS:
            return CITIZEN_ALREADY_EXISTS;
        case SET_SUCCESS:
            return CITIZEN_SUCCESS;
        default:return CITIZEN_SUCCESS;
    }
}
CitizenResult CityRemoveCitizen(City city, Citizen citizen){
    SetResult remove_result=setRemove(city->citizens,citizen);
   switch (remove_result){
     case SET_NULL_ARGUMENT:
         return CITIZEN_NULL_ARGUMENT;
     case SET_ITEM_DOES_NOT_EXIST:
         return CITIZEN_DOES_NOT_EXIST;
       case SET_SUCCESS:
           return CITIZEN_SUCCESS;
       default:return CITIZEN_SUCCESS;
   }
}
bool CityCompare(City old_city,City new_city){
    return old_city->id==new_city->id;
}
bool CityIsLegal(City city){
    return (*(city->id)>=FIRST_CITY_LEGAL_ID);
   // if(city==NULL)
     //   return CITY_NULL_ARGUMENT; you dont have to return null since u already checked that
}
//why u write GET when u get a bool?!
bool CityIsCandidateACitizen(City city,int candidate_to_be_id){

   // if(!(setIsIn(city->candidates,candidate)))
      //  return false;
      //if u return false here this means the candidate is not a citizen//so the error well send to the mtmelections well be false :(
      Citizen citizen=setGetFirst(city->citizens);
      while (citizen)
      {
          int citizen_id=CitizenGetid(citizen);
          if(citizen_id==candidate_to_be_id)return true;
          citizen=setGetNext(city->citizens);
      }
    return false;

    //return false were added!
}
/*MtmElectionsResult mtmElectionsAddCandidate(MtmElections mtmElections,
 * int candidateId, int cityId);
 * The above functions takes an int
 * City is above candidate, so it gets the int candidateId first, thus u do
 * all the validation, and just after that u create a Candidate object and insert
 * it.
*/
/* CityGetCitizen:
 * if the candidate does not belong to the city that we are searching in
 * the function will return NULL.
 */
Citizen CityGetCitizen(City city,int citizen_id){
    Citizen citizen=setGetFirst(city->citizens);
    while(CitizenGetid(citizen)!=citizen_id)
        citizen=setGetNext(city->citizens);
    return citizen;
}
CandidateResult CityInsertCandidate(City city, int candidate_id){
    if(city==NULL)return CANDIDATE_NULL_ARGUMENT;
    if(candidate_id<FIRST_CITIZEN_LEGAL_ID)//we said that we are not using numbers
        return CANDIDATE_ILLEGAL_ID;
    if(!CityIsCandidateACitizen(city,candidate_id))
        return CANDIDATE_CITIZEN_DOSE_NOT_EXIST;
    Citizen candidate_to_be=CityGetCitizen(city,candidate_id);
    Age candidate_to_be_age=NULL;
    CitizenGetInformation(candidate_to_be,candidate_to_be_age,CITIZEN_AGE);
    if(*candidate_to_be_age < CANDIDATE_MINIMUM_AGE)
        return CANDIDATE_AGE_NOT_APPROPRIATE;
    CitizenCandidateToBeRemovePrefrences(candidate_to_be);
    Candidate candidate=CandidateCreate();
    CandidateChangeId(candidate,candidate_id);
    SetResult add_candidate_result=setAdd(city->candidates,candidate);
    switch (add_candidate_result){
        case SET_NULL_ARGUMENT:
            return CANDIDATE_NULL_ARGUMENT;
        case SET_OUT_OF_MEMORY:
            return CANDIDATE_MEMORY_ERROR;
        case SET_ITEM_ALREADY_EXISTS:
            return CANDIDATE_ALREADY_EXISTS;
        default:return CANDIDATE_SUCCESS;
    }
}

void CityChangeInformation(City city,const String name,int id){
    *(city->id)=id;
   city->name=(String)malloc(sizeof(String*)*Stringlength(name));
    if(city->name==NULL){
        CityDestroy(city);
        return;
    }
    StringCopy(name,city->name);
//            StringCopy(name);
}
CandidateResult CityRemoveCandidate(City city,Candidate candidate) {
    SetResult result = setRemove(city->candidates, candidate);
    switch (result) {
        case SET_NULL_ARGUMENT:return CANDIDATE_NULL_ARGUMENT;
        case SET_ITEM_DOES_NOT_EXIST:return CANDIDATE_DOES_NOT_EXIST;
        default:return CANDIDATE_SUCCESS;
    }
}
//we assume here that the candidate is already a citizen!
CityResult  CitySupportCandidate(City city,Citizen citizen,int candidate_id,int priority) {
    Citizen candidate = CityGetCitizen(city, candidate_id);
    if (candidate == NULL)
        return CITY_NOT_THE_SAME_CITY;
    if (CitizenCandidateAlreadySupported(city, citizen, candidate_id, priority))
        return CITY_CANDIDATE_ALREADY_SUPPORTED;
   if (CityIsCandidate(city,candidate_id))
        return CITY_CITIZEN_CAN_NOT_SUPPORT;
    if(!(CitizenSupportCandidate(citizen,candidate_id,priority)))
        return CITY_CITIZEN_PRIORITY_EXISTS;
    return CITY_SUCCESS;
}

bool CityIsCandidate(City city,int candidate_id) {
    Candidate candidate = CandidateCreate();
    CandidateChangeId(candidate, candidate_id);
    if (setIsIn(city->candidates, candidate))
        return true;
    return false;
}
