
//
// Created by George on 12/2/2018.
//
#include "citizen.h"
#include "City.h"
#include "mtm_elections.h"
#include <stdio.h>
#include "mayor.h"
#include "set.h"
#include "mtm_print.h"
static void WriteWinners(Citizen citizen, const char* filename,int city_id,
        char * city_name);
static City mtmElectionsGetCity(MtmElections mtmElections,int general_id,
                                mtmElectionsGeneralInput desired_input);
static bool mtmElectionsIsLegal(int ,mtmElectionsGeneralInput );
static MtmElectionsResult MtmElectionsCitizenGetInformation(MtmElections
                                                            mtmElections,int citizenId,CitizenInformation information_type ,
                                                            int* information_new_copy);
static int mtmElectionsRankWithoutVoteVolume(MtmElections mtmElections,
                                             int citizen, void* pAge);
static MtmElectionsResult mtmElectionsMayorOfCityAux(MtmElections mtmElections,
        City city,Id mayor, RankFunc rank, void* auxilaryData,const char* filename);
static UniqueOrderedList mtmElectionsMayorToIds(UniqueOrderedList mayors
        ,MtmElections elections, const char * filename);
        //125:we never used this:
//static bool mtmElectionsIsCandidate(MtmElections mtmElections,int candidate_id);
struct mtm_elections_t{
  Set cities;
};
static void WriteWinners(Citizen citizen, const char* filename,int city_id,char * city_name) {
    FILE* file=fopen(filename,"a");
    if(!file)
        mtmPrintFileError(filename,file);
    mtmPrintMayorDetails(CitizenGetId(citizen),*(int*)CitizenGetInformation(citizen,CITIZEN_AGE)
    ,*(int*)CitizenGetInformation(citizen,CITIZEN_EDUCATION_YEARS),
    CitizenGetInformation(citizen,CITIZEN_NAME)
    ,city_name,city_id,file);
       fclose(file);

}
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

MtmElectionsResult mtmElectionsAddCity(MtmElections mtmElections, const char* cityName, int cityId){
    if(mtmElections==NULL ||cityName==NULL)
        return MTM_ELECTIONS_NULL_ARGUMENT;
    if(!(mtmElectionsIsLegal(cityId,GENERAL_ID)))
        return MTM_ELECTIONS_ILLEGAL_ID;
    City city=CityCreate();
    CityInsertInformation(city,(String)cityName,cityId);
    SetResult result=setAdd(mtmElections->cities,city);
    CityDestroy(city);
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
    *name=(Name)malloc(sizeof(*name)*length);
    if(*name ==NULL){
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
static MtmElectionsResult MtmElectionsCitizenGetInformation(MtmElections
                                                            mtmElections,int citizenId,CitizenInformation information_type ,
                                                            int* information_new_copy){
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
MtmElectionsResult mtmElectionsWithdrawCandidate(MtmElections mtmElections,
                                                 int candidateId, int cityId){
    if(mtmElections==DOES_NOT_EXIST)
        return MTM_ELECTIONS_NULL_ARGUMENT;
    if(!mtmElectionsIsLegal(candidateId,GENERAL_ID) ||
            !mtmElectionsIsLegal(cityId,GENERAL_ID))
        return MTM_ELECTIONS_ILLEGAL_ID;
    City candidate_city=
            mtmElectionsGetCity(mtmElections,cityId,GENERAL_CITY_ID);
    if(candidate_city==DOES_NOT_EXIST)
        return MTM_ELECTIONS_CITY_DOES_NOT_EXIST;
    if(CityGetCitizen(candidate_city,candidateId)==DOES_NOT_EXIST||
            !CityIsCandidate(candidate_city,candidateId))
        return MTM_ELECTIONS_CANDIDATE_DOES_NOT_EXIST;
    Candidate candidate=CandidateCreate();
    CandidateInsertInformation(candidate,candidateId);
    CityRemoveCandidate(candidate_city,candidate);
    CityCitizenRemovePrefrence(candidate_city,candidateId);
    CandidateDestroy(candidate);
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
        default:
            return MTM_ELECTIONS_SUCCESS;


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
MtmElectionsResult mtmElectionsChangeAddress(MtmElections mtmElections,
                                             int citizenId, int cityId) {
    if (mtmElections == DOES_NOT_EXIST)
        return MTM_ELECTIONS_NULL_ARGUMENT;
    if (!mtmElectionsIsLegal(cityId, GENERAL_CITY_ID)||
            !mtmElectionsIsLegal(citizenId, GENERAL_CITIZEN_ID))
        return MTM_ELECTIONS_ILLEGAL_ID;
    City citizen_city =
            mtmElectionsGetCity(mtmElections, citizenId, GENERAL_CITIZEN_ID);
    if (citizen_city == DOES_NOT_EXIST)
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    City citizen_new_city =
            mtmElectionsGetCity(mtmElections, cityId, GENERAL_CITY_ID);
    if (citizen_new_city == DOES_NOT_EXIST)
        return MTM_ELECTIONS_CITY_DOES_NOT_EXIST;
    Citizen current_citizen = CityGetCitizen(citizen_city, citizenId);
    if (CityIsCandidate(citizen_city, citizenId))
        mtmElectionsWithdrawCandidate(mtmElections, citizenId,
                                      CityGetId(citizen_city));

    if(CityInsertCitizen(citizen_new_city,
                         CitizenGetInformation(current_citizen, CITIZEN_NAME),
                         *(int *) CitizenGetInformation(current_citizen, CITIZEN_ID),
                         *(int *) CitizenGetInformation(current_citizen, CITIZEN_AGE),
                         *(int *) CitizenGetInformation(current_citizen,
                                                        CITIZEN_EDUCATION_YEARS))==
            CITIZEN_MEMORY_ERROR)
        return MTM_ELECTIONS_MEMORY_ERROR;
    CityRemoveCitizen(citizen_city, current_citizen);
    return MTM_ELECTIONS_SUCCESS;
}
int mtmElectionsRankByAge(MtmElections mtmElections, int citizen, void* pAge){
    if(mtmElections==DOES_NOT_EXIST||pAge==DOES_NOT_EXIST || !*(int*)pAge )
        return INT_NULL_ARGUMENT;
    City citizen_city=
            mtmElectionsGetCity(mtmElections,citizen,GENERAL_CITIZEN_ID);
    Citizen current_citizen=CityGetCitizen(citizen_city,citizen);
    if(current_citizen==DOES_NOT_EXIST)return NO_VOTES;
    return *((Age)CitizenGetInformation(current_citizen,CITIZEN_AGE))
            /(*(int*)pAge);

}
static int mtmElectionsRankWithoutVoteVolume(MtmElections mtmElections, int citizen, void* pAge){
    return mtmElectionsRankByAge(mtmElections,citizen,pAge)!=NO_VOTES;
}
UniqueOrderedList mtmElectionsPerformElections(MtmElections mtmElections,
                                               RankFunc rank, void* auxilaryData, const char* filename) {
    //we should check the file if null
    if (mtmElections == DOES_NOT_EXIST ||auxilaryData == DOES_NOT_EXIST
            ||filename==DOES_NOT_EXIST)
        return DOES_NOT_EXIST;

    UniqueOrderedList mayors=uniqueOrderedListCreate((copyElements)VoteCopy,
                                                     (freeElements)VoteDestroy,(elementsEquals)VoteIsEqual,
                                                     (elementGreaterThan)VoteElectionsGreaterThan);
    SET_FOREACH(City, city, mtmElections->cities) {
        int mayor_id ;
        int voter_minimum_age=VOTER_MINIMUM_AGE;
        MtmElectionsResult city_result;
        if (rank == DOES_NOT_EXIST)
            city_result = mtmElectionsMayorOfCityAux(mtmElections,
                                                     city, &mayor_id, mtmElectionsRankWithoutVoteVolume,
                                                     &voter_minimum_age,filename);
        else
            city_result =  mtmElectionsMayorOfCityAux(mtmElections,
                                                      city, &mayor_id, rank,
                                                      auxilaryData,filename);

        if(city_result==MTM_ELECTIONS_NO_CANDIDATES_IN_CITY)continue;
        if(city_result==MTM_ELECTIONS_MEMORY_ERROR)
            return NULL;
        Citizen mayor=CityGetCitizen(city,mayor_id);
        Vote mayor_votes=VoteCreate();
        VoteInsertInformation(mayor_votes,mayor_id,
                              CitizenGetInformation(mayor,CITIZEN_NAME),
                              mayor_id);
        if(uniqueOrderedListInsert(mayors,mayor_votes)
                ==UNIQUE_ORDERED_LIST_OUT_OF_MEMORY)
            return NULL;
        VoteDestroy(mayor_votes);

    }

    return mtmElectionsMayorToIds(mayors,mtmElections,filename);

}
static UniqueOrderedList mtmElectionsMayorToIds(UniqueOrderedList mayors
        ,MtmElections elections, const char * filename){
    Vote iterator=uniqueOrderedListGetLowest(mayors);
    UniqueOrderedList mayors_ids= uniqueOrderedListCreate(copyInt, freeInt, intEquals, intGreaterThan);

    while(iterator) {
        int mayor_id= VoteCandidateGetId(iterator);
        City city=mtmElectionsGetCity(elections,mayor_id,GENERAL_CITIZEN_ID);
        //printf("%d\n",mayor_id);
        WriteWinners(CityGetCitizen(city,mayor_id),filename,CityGetId(city),CityGetName(city));

        if(uniqueOrderedListInsert(mayors_ids,&mayor_id)==UNIQUE_ORDERED_LIST_OUT_OF_MEMORY)
            return NULL;
        iterator= uniqueOrderedListGetNext(mayors);
    }
    uniqueOrderedListDestroy(mayors);
    return mayors_ids;
}
MtmElectionsResult mtmElectionsMayorOfCity(MtmElections mtmElections,
                                           int cityId, int* mayor, const char* filename){
    //check the file name if it hasnt to be null
    if(mtmElections==DOES_NOT_EXIST||mayor==DOES_NOT_EXIST||
            filename==DOES_NOT_EXIST)
        return MTM_ELECTIONS_NULL_ARGUMENT;
    if(!mtmElectionsIsLegal(cityId,GENERAL_CITY_ID))
        return MTM_ELECTIONS_ILLEGAL_ID;
    City city=mtmElectionsGetCity(mtmElections,cityId,GENERAL_CITY_ID);
    if(city==DOES_NOT_EXIST)
        return MTM_ELECTIONS_CITY_DOES_NOT_EXIST;
    int minimum_voter_age=VOTER_MINIMUM_AGE;
    // CityResult city_votes_result=
  //  printf("%d :",*mayor);
   // printf("%d",CityGetId(city));

    MtmElectionsResult result= mtmElectionsMayorOfCityAux(mtmElections,city,
                                      mayor,mtmElectionsRankWithoutVoteVolume,&minimum_voter_age,filename);
    if(result != MTM_ELECTIONS_NO_CANDIDATES_IN_CITY)
    WriteWinners(CityGetCitizen(city,*mayor),filename,CityGetId(city),CityGetName(city));
     return result;
}
static MtmElectionsResult mtmElectionsMayorOfCityAux(MtmElections mtmElections,
                                                     City city,Id mayor, RankFunc rank, void* auxilaryData,const char* filename){
    if(city==DOES_NOT_EXIST||mayor==NULL)
        return MTM_ELECTIONS_NULL_ARGUMENT;
    // if(!CityIsLegal(city))return FIRST_CITY_LEGAL_ID;
    if(setGetFirst(CityGetCandidates(city))==DOES_NOT_EXIST)//get candidates
        return MTM_ELECTIONS_NO_CANDIDATES_IN_CITY;
    UniqueOrderedList votes=uniqueOrderedListCreate((copyElements)VoteCopy,
                                                    (freeElements)VoteDestroy,(elementsEquals)VoteIsEqual,
                                                    (elementGreaterThan)VoteGreaterThan);
    SET_FOREACH(Citizen,citizen,CityGetCitizens(city)){//get citizens
        void* citizen_age_pointer=CitizenGetInformation(citizen,CITIZEN_AGE);
        int citizen_age= *(int*)(citizen_age_pointer);
        if(citizen_age<VOTER_MINIMUM_AGE)continue;
        Preference citizen_vote=CitizenGetPreferredCandidate(citizen);
        if(citizen_vote==DOES_NOT_EXIST)continue;
        int candidate_id =PreferenceGetCandidateId(citizen_vote);
        Vote new_vote=VoteCreate();
        Vote old_vote= CityGetCandidateVote(votes,candidate_id);

        Citizen candidate=CityGetCitizen(city,candidate_id);
        int vote_volume=rank(mtmElections,*((int*)CitizenGetInformation(citizen,
                                                                        CITIZEN_ID)),auxilaryData);
        VoteInsertInformation(new_vote,candidate_id,
                              (String)CitizenGetInformation(candidate,CITIZEN_NAME),
                              VoteCandidateGetVotes(old_vote)+vote_volume);

        if(CityUpdateCandidateVotes(votes,new_vote,old_vote)==CITY_MEMORY_ERROR)
            return MTM_ELECTIONS_MEMORY_ERROR;
        VoteDestroy(new_vote);
    }

    *mayor=VoteCandidateGetId(uniqueOrderedListGetLowest(votes));
    uniqueOrderedListDestroy(votes);
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
    }
    return DOES_NOT_EXIST;

}

