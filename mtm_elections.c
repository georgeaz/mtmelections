//
// Created by George on 12/2/2018.
//
#include "citizen.h"
#include "mtm_elections.h"
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
bool mtmElectionsIsLegal(int input,mtmElectionsGeneralInput type){
    switch(type){
        case GENERAL_ID:return input>0;
        //cases GENERAL_ID or GENERAL_EDUCATION_YEARS are handled the same way,
        //and they are the only left cases to handle! so:
        default:return input>=0;
        case :break;
        case GENERAL_EDUCATION_YEARS:break;
        //ymaaaaaaa shu b7b lina
    }
}
