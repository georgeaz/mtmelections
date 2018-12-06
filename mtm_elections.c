//
// Created by George on 12/2/2018.
//
#include "citizen.h"
#include "City.h"
#include "mtm_elections.h"
#include <stdio.h>
static City mtmElectionsGetCity(MtmElections mtmElections,int general_id,
                                mtmElectionsGeneralInput desired_input);
static bool mtmElectionsIsLegal(int ,mtmElectionsGeneralInput );
static MtmElectionsResult MtmElectionsCitizenGetInformation(MtmElections
mtmElections,int citizenId,CitizenInformation information_type ,int* information_new_copy);
//125:we never used this:
//static bool mtmElectionsIsCandidate(MtmElections mtmElections,int candidate_id);
struct mtm_elections_t{
  Set cities;
};
MtmElections mtmElectionsCreate(){
    MtmElections elections=(MtmElections)malloc(sizeof(*elections));
    if(elections==NULL)
        return NULL;
    Set cities=setCreate((copySetElements)CityCopy,(freeSetElements)CityDestroy,
            (compareSetElements)CityCompare);
    if(cities==NULL){
        free(elections);
        return NULL;
    }
    elections->cities=cities;
    return elections;
}
void mtmElectionsDestroy(MtmElections mtmElections){
    if(mtmElections==NULL)return;
    setDestroy(mtmElections->cities);
    free(mtmElections);
}
void ElectionsPrint(MtmElections mtmElections){
    SET_FOREACH(City,city,mtmElections->cities)
    CityPrint(city);
}
MtmElectionsResult mtmElectionsAddCity(MtmElections mtmElections, const char* cityName, int cityId){
    if(mtmElections==NULL ||cityName==NULL)
        return MTM_ELECTIONS_NULL_ARGUMENT;
    if(!(mtmElectionsIsLegal(cityId,GENERAL_ID)))
        return MTM_ELECTIONS_ILLEGAL_ID;
    City city=CityCreate();
    CityInsertInformation(city,(String)cityName,cityId);
    SetResult result=setAdd(mtmElections->cities,city);

    switch (result){
        case SET_ITEM_ALREADY_EXISTS://we should destroy the city we created
            return MTM_ELECTIONS_CITY_ALREADY_EXISTS;
        case SET_NULL_ARGUMENT:
            return MTM_ELECTIONS_MEMORY_ERROR;
        case SET_OUT_OF_MEMORY:
            return MTM_ELECTIONS_MEMORY_ERROR;
        default:
            return MTM_ELECTIONS_SUCCESS;
    }
}
MtmElectionsResult mtmElectionsAddCitizen(MtmElections mtmElections,
 const char* citizenName, int citizenId, int citizenAge, int yearsOfEducation,
 int cityId){
    if(mtmElections==NULL||citizenName==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    if(!mtmElectionsIsLegal(citizenId,GENERAL_ID)||
    !mtmElectionsIsLegal(cityId,GENERAL_ID))
        return MTM_ELECTIONS_ILLEGAL_ID;
    if(!mtmElectionsIsLegal(citizenAge,GENERAL_AGE))
        return MTM_ELECTIONS_ILLEGAL_AGE;
    if(!mtmElectionsIsLegal(yearsOfEducation,GENERAL_EDUCATION_YEARS))
        return MTM_ELECTIONS_ILLEGAL_NUMBER_OF_YEARS;
    if(mtmElectionsGetCity(mtmElections,citizenId,GENERAL_CITIZEN_ID)!=
    DOES_NOT_EXIST)
        return MTM_ELECTIONS_CITIZEN_ALREADY_EXISTS;
    City citizen_chosen_city=
            mtmElectionsGetCity(mtmElections,cityId,GENERAL_CITY_ID);
    if(citizen_chosen_city==DOES_NOT_EXIST)
        return MTM_ELECTIONS_CITY_DOES_NOT_EXIST;
    if(CityInsertCitizen(citizen_chosen_city,(String)citizenName,citizenId,citizenAge,
            yearsOfEducation)==CITIZEN_MEMORY_ERROR)
        return MTM_ELECTIONS_MEMORY_ERROR;
    return MTM_ELECTIONS_SUCCESS;

}
MtmElectionsResult MtmElectionsCitizenGetName(MtmElections mtmElections, int citizenId, Name* name){
    if(mtmElections==NULL||name==NULL)
        return MTM_ELECTIONS_NULL_ARGUMENT;
    if(!(mtmElectionsIsLegal(citizenId,GENERAL_ID)))
        return MTM_ELECTIONS_ILLEGAL_ID;
    City city=mtmElectionsGetCity(mtmElections,citizenId,GENERAL_CITIZEN_ID);
    if(city==DOES_NOT_EXIST)
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    char* name_copy=
            CitizenGetInformation(CityGetCitizen(city,citizenId),CITIZEN_NAME);
    size_t length=Stringlength(name_copy);
    name=(Name*)malloc(sizeof(*name)*length);
    if(name ==NULL){
        return MTM_ELECTIONS_MEMORY_ERROR;
    }
    StringCopy(name_copy,*name);
    return MTM_ELECTIONS_SUCCESS;
}
MtmElectionsResult MtmElectionsCitizenGetCity(MtmElections mtmElections, int citizenId, int* cityId){
    if(mtmElections==NULL ||cityId==NULL)
        return MTM_ELECTIONS_NULL_ARGUMENT;
    return MtmElectionsCitizenGetInformation(mtmElections,citizenId,CITIZEN_CITY_ID,cityId);
}
MtmElectionsResult MtmElectionsCitizenGetAge(MtmElections mtmElections, int citizenId, int* age){
    if(mtmElections==NULL || age==NULL)
        return MTM_ELECTIONS_NULL_ARGUMENT;
    return  MtmElectionsCitizenGetInformation(mtmElections,citizenId,CITIZEN_AGE,age);

}
MtmElectionsResult MtmElectionsCitizenGetEducation(MtmElections mtmElections, int citizenId, int* yearsOfEducation){
    if(mtmElections==NULL || yearsOfEducation==NULL)
        return MTM_ELECTIONS_NULL_ARGUMENT;
    return MtmElectionsCitizenGetInformation(mtmElections,citizenId,CITIZEN_EDUCATION_YEARS,yearsOfEducation);
}

static MtmElectionsResult MtmElectionsCitizenGetInformation(MtmElections mtmElections,int citizenId,
                                                CitizenInformation information_type ,int* information_new_copy){
    if(!(mtmElectionsIsLegal(citizenId,GENERAL_ID)))
        return MTM_ELECTIONS_ILLEGAL_ID;
    City city=mtmElectionsGetCity(mtmElections,citizenId,GENERAL_CITIZEN_ID);
    if(city==DOES_NOT_EXIST)
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    //information_new_copy=(int*)malloc(sizeof(*information_new_copy));
    if(information_new_copy==NULL)
        return MTM_ELECTIONS_MEMORY_ERROR;
    if(information_type==CITIZEN_CITY_ID){
        *information_new_copy=CityGetId(city);
        return MTM_ELECTIONS_SUCCESS;
    }
    Citizen citizen=CityGetCitizen(city,citizenId);
    *information_new_copy=*((int*)CitizenGetInformation(citizen,information_type));
    return MTM_ELECTIONS_SUCCESS;
}
MtmElectionsResult  mtmElectionsAddCandidate(MtmElections mtmElections,
        int candidateId, int cityId){

    if(mtmElections==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    if(!mtmElectionsIsLegal(cityId,GENERAL_CITY_ID)||
    !mtmElectionsIsLegal(candidateId,GENERAL_CANDIDATE_ID))
        return MTM_ELECTIONS_ILLEGAL_ID;
    City candidate_city=
            mtmElectionsGetCity(mtmElections,cityId,GENERAL_CITY_ID);
    if(candidate_city==DOES_NOT_EXIST)
        return MTM_ELECTIONS_CITY_DOES_NOT_EXIST;
    Citizen candidate_to_be=CityGetCitizen(candidate_city,candidateId);
    if(candidate_to_be==DOES_NOT_EXIST)
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    Age candidate_age= CitizenGetInformation(candidate_to_be,CITIZEN_AGE);
    if(*candidate_age<CANDIDATE_MINIMUM_AGE)
        return MTM_ELECTIONS_AGE_NOT_APPROPRIATE;
    CandidateResult result= CityInsertCandidate(candidate_city,candidateId);
    switch (result){
        case CANDIDATE_MEMORY_ERROR:
            return MTM_ELECTIONS_MEMORY_ERROR;
        case CANDIDATE_ALREADY_EXISTS:
            return MTM_ELECTIONS_CANDIDATE_ALREADY_EXISTS;
        default:return MTM_ELECTIONS_SUCCESS;
    }
}
MtmElectionsResult mtmElectionsWithdrawCandidate(MtmElections mtmElections, int candidateId, int cityId){
    if(mtmElections==DOES_NOT_EXIST)
        return MTM_ELECTIONS_NULL_ARGUMENT;
    if(!mtmElectionsIsLegal(candidateId,GENERAL_ID) ||
    !mtmElectionsIsLegal(cityId,GENERAL_ID))
        return MTM_ELECTIONS_ILLEGAL_ID;
    City candidate_city=
            mtmElectionsGetCity(mtmElections,cityId,GENERAL_CITY_ID);
    if(candidate_city==DOES_NOT_EXIST)
        return MTM_ELECTIONS_CITY_DOES_NOT_EXIST;
    if(CityGetCitizen(candidate_city,candidateId)==DOES_NOT_EXIST)
        return MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST;
    Candidate candidate=CandidateCreate();
    CandidateInsertInformation(candidate,candidateId);
    CityRemoveCandidate(candidate_city,candidate);
    CityCitizenRemovePrefrence(candidate_city,candidateId);
    return MTM_ELECTIONS_SUCCESS;
}
MtmElectionsResult mtmElectionsSupportCandidate(MtmElections mtmElections,
        int citizenId, int candidateId, int priority){
    if(mtmElections==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    if(!mtmElectionsIsLegal(candidateId,GENERAL_CITY_ID)||
            !mtmElectionsIsLegal(citizenId,GENERAL_CITIZEN_ID))
        return MTM_ELECTIONS_ILLEGAL_ID;
    if(!mtmElectionsIsLegal(priority,GENERAL_CITIZEN_PRIORITY))
        return MTM_ELECTIONS_ILLEGAL_PRIORITY;
    City citizen_city=
            mtmElectionsGetCity(mtmElections,citizenId,GENERAL_CITIZEN_ID);

    Citizen citizen=CityGetCitizen(citizen_city,citizenId);
    if(citizen_city==DOES_NOT_EXIST)
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    City candidate_city=
            mtmElectionsGetCity(mtmElections,candidateId,GENERAL_CANDIDATE_ID);
    if(candidate_city==DOES_NOT_EXIST||!CityIsCandidate(candidate_city,candidateId))
        return MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST;
    CityResult result=
            CitySupportCandidate(citizen_city,citizen,candidateId,priority);
    switch (result){
        case CITY_NOT_THE_SAME_CITY:
            return MTM_ELECTIONS_NOT_SAME_CITY;
        case CITY_CANDIDATE_ALREADY_SUPPORTED:
            return MTM_ELECTIONS_ALREADY_SUPPORTED;
        case  CITY_CITIZEN_CAN_NOT_SUPPORT :
            return MTM_ELECTIONS_CAN_NOT_SUPPORT;
        case CITY_CITIZEN_PRIORITY_EXISTS:
            return MTM_ELECTIONS_PRIORITY_EXISTS;
        default:return MTM_ELECTIONS_SUCCESS;
    }
}
MtmElectionsResult mtmElectionsCancelSupport(MtmElections mtmElections,
        int citizenId, int candidateId){
    if(mtmElections==NULL)return MTM_ELECTIONS_NULL_ARGUMENT;
    if(!mtmElectionsIsLegal(candidateId,GENERAL_CITY_ID)||
            !mtmElectionsIsLegal(citizenId,GENERAL_CITIZEN_ID))
        return MTM_ELECTIONS_ILLEGAL_ID;
    Citizen citizen=
            CityGetCitizen(mtmElectionsGetCity(mtmElections,citizenId,
                    GENERAL_CITIZEN_ID),citizenId);
         if(citizen==DOES_NOT_EXIST)
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    City candidate_city=
            mtmElectionsGetCity(mtmElections,candidateId,GENERAL_CANDIDATE_ID);
    if(candidate_city==DOES_NOT_EXIST||!CityIsCandidate(candidate_city,candidateId))
        return MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST;
    if(citizenId==candidateId)
        return MTM_ELECTIONS_MUST_SUPPORT;
    if(CitizenRemovePrefrence(citizen,candidateId)
        ==CITIZEN_DOES_NOT_SUPPORT_CANDIDATE)
        return MTM_ELECTIONS_NOT_SUPPORTED;
    return MTM_ELECTIONS_SUCCESS;
}
static bool mtmElectionsIsLegal(int input,mtmElectionsGeneralInput type){
    switch(type){
        case GENERAL_AGE:
            return (input>0);
        /*cases GENERAL_CITIZEN_PRIORITY orGENERAL_ID or GENERAL_EDUCATION_YEARS
        * are handled the same way,
        *and they are the only left cases to handle! so:*/
    //    default:return input>=0;
        default:
            return (input>=0);
    }
    return true;
}
static City mtmElectionsGetCity(MtmElections mtmElections,int general_id,
        mtmElectionsGeneralInput desired_input){
    SET_FOREACH(City,city,mtmElections->cities){
        if(desired_input==GENERAL_CITY_ID&&CityGetId(city)==general_id)
            return city;
          if(desired_input==GENERAL_CITIZEN_ID||desired_input==GENERAL_CANDIDATE_ID)
              if(CityGetCitizen(city,general_id)!=DOES_NOT_EXIST) {
                  return city;
              }
        /*
        switch (desired_input){
            case GENERAL_CITY_ID:{
                if(CityGetId(city)==general_id){
                    if(general_id==25){
                        printf("zbrora");
                    }
                    return city;}
                }


                *//*The default case is for handling GENERAL_CITIZEN_ID and
                 * GENERAL_CANDIDATE_ID because every candidate is a citizen
                 * at last.
                 * *//*
            case GENERAL_CITIZEN_ID:
                if(CityGetCitizen(city,general_id)!=DOES_NOT_EXIST){
                    return city;
                }
            default:
                if(CityGetCitizen(city,general_id)!=DOES_NOT_EXIST)return city;
        }
*/
    }
    return DOES_NOT_EXIST;

}
