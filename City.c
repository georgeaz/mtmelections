//
// Created by User on 28/11/2018.
//

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "City.h"
#include "set.h"
struct City_t{
    Id id;
    String name;
    Set citizens;
    Set candidates;

};
int CityGetId(City city){
    return *(city->id);
}
String CityGetName(City city){
    return  city->name;
}
Set CityGetCitizens(City city){
    return city->citizens;
}
Set CityGetCandidates(City city){
    return city->candidates;
}
void CityDestroy(City city){
    if(city==NULL)return ;
   free(city->name);
   free(city->id);
    setDestroy(city->citizens);
    setDestroy(city->candidates);
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
    setDestroy(new_city->citizens);
    setDestroy(new_city->candidates);
    new_city->citizens=setCopy(source_city->citizens);
    new_city->candidates=setCopy(source_city->candidates);
    new_city->name=(String)malloc(sizeof(String*)*Stringlength(source_city->name));
    StringCopy(source_city->name,new_city->name);
    *(new_city->id)=*(source_city->id);
    if(new_city->name==NULL||new_city->citizens==NULL){
        CityDestroy(new_city);
        return NULL;
    }
        return new_city;
}
CitizenResult CityInsertCitizen(City city,const String citizen_name,
        int citizen_id, int citizen_age, int education_years){
        //the whole function were replaced
        Citizen new_citizen=CitizenCreate();
        if(new_citizen==NULL)return CITIZEN_MEMORY_ERROR;
        CitizenInsertInformation(new_citizen,citizen_id,citizen_name,
                education_years,citizen_age);
    SetResult result=setAdd(city->citizens,new_citizen);
    CitizenDestroy(new_citizen);
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

int CityCompare(City old_city,City new_city){
   return (CityGetId(old_city)-CityGetId(new_city));
}

Citizen CityGetCitizen(City city,int citizen_id){
   if(city==DOES_NOT_EXIST)
       return DOES_NOT_EXIST;
    SET_FOREACH(Citizen,citizen,city->citizens)
    if(CitizenGetId(citizen)==citizen_id)
        return citizen;
    return DOES_NOT_EXIST;
}
CandidateResult CityInsertCandidate(City city, int candidate_id){
    if(city==NULL)return CANDIDATE_NULL_ARGUMENT;
    Citizen candidate_to_be=CityGetCitizen(city,candidate_id);
    CitizenCandidateToBeRemovePrefrences(candidate_to_be);
    Candidate candidate=CandidateCreate();
    CandidateInsertInformation(candidate,candidate_id);
    SetResult add_candidate_result=setAdd(city->candidates,candidate);
    CandidateDestroy(candidate);
    switch (add_candidate_result){
        case SET_NULL_ARGUMENT:
            return CANDIDATE_NULL_ARGUMENT;
        case SET_OUT_OF_MEMORY:
            return CANDIDATE_MEMORY_ERROR;
        case SET_ITEM_ALREADY_EXISTS:
            return CANDIDATE_ALREADY_EXISTS;
        default:{
            CitizenSupportCandidate(candidate_to_be,candidate_id,0);
            return CANDIDATE_SUCCESS;}

    }
}
void CityInsertInformation(City city, const String name, int id){
    *(city->id)=id;
   city->name=(String)malloc(sizeof(String*)*Stringlength(name));
    if(city->name==NULL){
        CityDestroy(city);
        return;
    }
    StringCopy(name,city->name);
}
CandidateResult CityRemoveCandidate(City city,Candidate candidate) {
    SetResult result = setRemove(city->candidates, candidate);
    switch (result) {
        case SET_NULL_ARGUMENT:return CANDIDATE_NULL_ARGUMENT;
        case SET_ITEM_DOES_NOT_EXIST:return CANDIDATE_DOES_NOT_EXIST;
        default:return CANDIDATE_SUCCESS;
    }
}
CityResult  CitySupportCandidate(City city,Citizen citizen,int candidate_id,int priority) {
    Citizen candidate = CityGetCitizen(city, candidate_id);
    if (candidate == NULL)
        return CITY_NOT_THE_SAME_CITY;
    if (CitizenIsCandidateSupported(city, citizen, candidate_id))
            return CITY_CANDIDATE_ALREADY_SUPPORTED;
   if (CityIsCandidate(city, CitizenGetId(citizen)))
        return CITY_CITIZEN_CAN_NOT_SUPPORT;
    if(!(CitizenSupportCandidate(citizen,candidate_id,priority)))
        return CITY_CITIZEN_PRIORITY_EXISTS;

    return CITY_SUCCESS;
}
void CityCitizenRemovePrefrence(City city,int candidate_id){
    SET_FOREACH(Citizen,citizen,city->citizens)
    CitizenRemovePrefrence( citizen,candidate_id);
}
bool CityIsCandidate(City city,int candidate_id) {
    Candidate candidate = CandidateCreate();
    CandidateInsertInformation(candidate, candidate_id);
    if (setIsIn(city->candidates, candidate)) {
        CandidateDestroy(candidate);
        return true;
    }
    CandidateDestroy(candidate);
    return false;
}
Vote CityGetCandidateVote(UniqueOrderedList votes, int candidate_id){

    Vote votes_ptr=uniqueOrderedListGetLowest(votes);
    while(votes_ptr){
        if(VoteCandidateGetId(votes_ptr)==candidate_id){
            return votes_ptr;}
        votes_ptr=uniqueOrderedListGetNext(votes);
    }
    return NO_VOTES;
}
CityResult CityUpdateCandidateVotes(UniqueOrderedList votes,Vote new_vote, Vote
old_vote){
        uniqueOrderedListRemove(votes,old_vote);
    UniqueOrderedListResult insert_result=
            uniqueOrderedListInsert(votes,new_vote);
    switch (insert_result){
        case UNIQUE_ORDERED_LIST_OUT_OF_MEMORY:return CITY_MEMORY_ERROR;
        case UNIQUE_ORDERED_LIST_NULL_ARGUMENT:return CITY_NULL_ARGUMENT;
        case UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS:return CITY_ALREADY_EXISTS;
        default:return CITY_SUCCESS;
    }

}
