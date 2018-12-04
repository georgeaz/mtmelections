//
// Created by George on 12/2/2018.
//
#include "citizen.h"
#include "City.h"
#include "mtm_elections.h"
static bool mtmElectionsIsCitizen(MtmElections ,int citizen_id);
static City mtmElectionsGetCity(MtmElections ,int city_id);
static bool mtmElectionsIsLegal(int ,mtmElectionsGeneralInput );

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
    if(mtmElectionsIsCitizen(mtmElections,citizenId))
        return MTM_ELECTIONS_CITIZEN_ALREADY_EXISTS;
    City citizen_chosen_city=mtmElectionsGetCity(mtmElections,cityId);
    if(citizen_chosen_city==DOES_NOT_EXIST)
        return MTM_ELECTIONS_CITIZEN_DOES_NOT_EXIST;
    if(CityInsertCitizen(citizen_chosen_city,citizenName,citizenId,citizenAge,
            yearsOfEducation)==CITIZEN_MEMORY_ERROR)
        return MTM_ELECTIONS_MEMORY_ERROR;
    return MTM_ELECTIONS_SUCCESS;
}
static bool mtmElectionsIsLegal(int input,mtmElectionsGeneralInput type){
    switch(type){
        case GENERAL_AGE:return input>0;
        //cases GENERAL_ID or GENERAL_EDUCATION_YEARS are handled the same way,
        //and they are the only left cases to handle! so:
        default:return input>=0;
        case GENERAL_ID:break;
        case GENERAL_EDUCATION_YEARS:break;
    }
}
 static bool mtmElectionsIsCitizen(MtmElections mtmElections,int citizen_id){
    SET_FOREACH(City,city,mtmElections->cities)
     if(CityGetCitizen(city,citizen_id)!=NULL)
         return true;
}
static City mtmElectionsGetCity(MtmElections mtmElections,int city_id){
    SET_FOREACH(City,city,mtmElections->cities)
    if(CityGetId(city)==city_id)return city;
    return NULL;

}
