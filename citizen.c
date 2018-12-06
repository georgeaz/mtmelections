//
// Created by George on 11/29/2018.
//
#include "citizen.h"
#include "uniqueOrderedList/uniqueOrderedList.h"
#include "preference.h"
#include <stdlib.h>
#include <stdio.h>
//we should include this in general functions
struct Citizen_t{
  Name name;
  Age age;
  Id id;
  EducationYears education_years;
  UniqueOrderedList prefrences;
};
void PrintCitizen(Citizen citizen){

    printf("Citizen Name:%s\n",citizen->name);
    printf("Citizen Age:%d\n",*citizen->age);
    printf("Citizen ID:%d\n",*citizen->id);
    printf("Citizen Education Years:%d\n",*citizen->education_years);
    printf("----------------------\n");

}

Citizen CitizenCreate(){
    //malloc for name will be added in copy, since we dont know the size of name yet
    Citizen citizen=(Citizen)malloc(sizeof(*citizen));
    Age age=(Age)malloc(sizeof(*age));
    Id id=(Id)malloc(sizeof(*id));
    EducationYears education_years=(EducationYears)malloc(sizeof(*education_years));
    UniqueOrderedList citizen_prefrences= uniqueOrderedListCreate((copyElements) PreferenceCopy,
                                                                  (freeElements) PreferenceDestroy,
                                                                  (elementsEquals) PreferenceIsEqual,
                                                                  (elementGreaterThan) PreferenceCompare);
    if(citizen==NULL||age==NULL||id==NULL||education_years==NULL||citizen_prefrences==NULL){
        free(citizen);
        free(age);
        free(id);
        free(education_years);
        uniqueOrderedListDestroy(citizen_prefrences);
        return NULL;
    }
    citizen->age=age;
    citizen->id=id;
    citizen->education_years=education_years;
    citizen->prefrences=citizen_prefrences;
    return citizen;
}
void CitizenDestroy(Citizen citizen)
{
    //always check if  object==NULL before accessing struct fields!
    if(citizen==NULL) return;
    free(citizen->age);
    free(citizen->education_years);
    free(citizen->id);
    uniqueOrderedListDestroy(citizen->prefrences);
    free(citizen);

}
Citizen CitizenCopy(Citizen source_citizen){
    Citizen new_citizen=CitizenCreate();

    if(source_citizen==NULL||new_citizen==NULL)
        return NULL;
    //we should check this!
//    *(new_citizen->name)=StringCopy(*(new_citizen->name));
    new_citizen->name=(String)malloc(sizeof(String*)*Stringlength(source_citizen->name));
    new_citizen->prefrences=uniqueOrderedListCopy(source_citizen->prefrences);
    if(new_citizen->name==NULL||new_citizen->prefrences==NULL){
        CitizenDestroy(new_citizen);
        return NULL;
    }
    StringCopy(source_citizen->name,new_citizen->name);
    new_citizen->id=source_citizen->id;
    new_citizen->education_years=source_citizen->education_years;
    new_citizen->age=source_citizen->age;
    return new_citizen;
}
/*
 * returns CITIZEN_ALREADY_SIPPORETED in case of the citizen is already supporting this candidate, otherwise, CITIZEN_SUCCESS
 */
bool CitizenCandidateAlreadySupported(City city, Citizen citizen, int candidate_id,int priority) {
    Preference citizen_preference=PreferenceCreate();
    PreferenceInsertInformation(citizen_preference, candidate_id, priority);
    Preference citizen_old_preference = CitizenFindPrefernce(citizen,candidate_id);
    if(!citizen_old_preference)
        return false ;
    return true;
   // UniqueOrderedList result=uniqueOrderedListInsert(citizen->prefrences,citizen_preference);

    //switch(result

}
int CitizenCompare(Citizen old_citizen,Citizen new_citizen){
    return *(old_citizen->id)-*(new_citizen->id);
}

void* CitizenGetInformation(Citizen citizen,CitizenInformation desirable_information) {
    //للأمانة انا غير متأكد من الدالّة يا لينا الع!
    switch (desirable_information) {
        case CITIZEN_ID:return (citizen->id);
        case CITIZEN_NAME:return  (citizen->name);
        case CITIZEN_EDUCATION_YEARS:return (citizen->education_years);
        case CITIZEN_AGE:return  (citizen->age);
        default:return NULL;
    }
}
void CitizenCandidateToBeRemovePrefrences(Citizen citizen){
    uniqueOrderedListClear(citizen->prefrences);
}
Preference CitizenFindPrefernce(Citizen citizen,int candidate_id) {
    Preference vote = uniqueOrderedListGetLowest(citizen->prefrences);
    while (vote) {
        if (PreferenceCandidateGetId(vote) == candidate_id)
            return vote;
        vote = uniqueOrderedListGetNext(citizen->prefrences);
    }
    return vote;
}
CitizenResult CitizenRemovePrefrence(Citizen citizen, int candidate_id ){
    Preference vote =CitizenFindPrefernce(citizen,candidate_id);
    if(vote==DOES_NOT_EXIST)
        return CITIZEN_DOES_NOT_SUPPORT_CANDIDATE;
    uniqueOrderedListRemove(citizen->prefrences, vote);
    return CITIZEN_SUCCESS;
}
/*Preference CitizenGetPrefrence(Citizen citizen,int candidate_id)
{lina 3m tl3b m3 juleeeeeeeee bs wleshy kter w wow !!!!
 wow
 jd wow
gogo wq7...
    Preference preference=uniqueOrderedListGetLowest(citizen->prefrences);
    while(preference) {
        if(PreferenceCandidateGetId(preference)==candidate_id){
        }
    }
}*/
int CitizenGetid(Citizen citizen){
    if(citizen==NULL)return NOT_FOUND;
    return *(citizen->id);
}
//maybe no:

void CitizenInsertInformation(Citizen citizen,int id,const String name,int education_years,int age){
    *(citizen->id)=id;
    citizen->name=(String)malloc(sizeof(String*)*Stringlength(name));
    if(citizen->name==NULL){
        CitizenDestroy(citizen);
        return;
    }
    StringCopy(name,citizen->name);
    *(citizen->age)=age;
    *(citizen->education_years)=education_years;
}
bool CitizenSupportCandidate(Citizen citizen,int candidate_id,int priority){
    Preference vote=PreferenceCreate();
    PreferenceInsertInformation(vote, candidate_id, priority);
    if(uniqueOrderedListInsert(citizen->prefrences,vote)==UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS)
        return false;
    return true;
}