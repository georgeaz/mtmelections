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
    //zbe
    //Name name=(Name)malloc(sizeof(*name));
    //malloc for name will be added in copy, since we dont know the size of name
    Citizen citizen=(Citizen)malloc(sizeof(*citizen));
    Age age=(Age)malloc(sizeof(*age));
    Id id=(Id)malloc(sizeof(*id));
    EducationYears education_years=(EducationYears)malloc(sizeof(*education_years));
    UniqueOrderedList citizen_prefrences=uniqueOrderedListCreate((copyElements)PreferenceCopy,(freeElements)PreferenceDestroy,(elementsEquals)PreferenceIsEquals,(elementGreaterThan)PreferenceCompare);
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
    Vote citizen_preference=PreferenceCreate();
    PreferenceChangeInformation(citizen_preference,candidate_id,priority);
    Vote citizen_old_preference = CitizenFindPrefernce(citizen,candidate_id);
    if(!citizen_old_preference)
        return false ;
    return true;
   // UniqueOrderedList result=uniqueOrderedListInsert(citizen->prefrences,citizen_preference);

    //switch(result

}
bool CitizenCompere(Citizen old_citizen,Citizen new_citizen){
    return old_citizen->id==new_citizen->id;
}

void CitizenGetInformation(Citizen citizen,Information information,CitizenInformation desirable_information) {
    //للأمانة انا غير متأكد من الدالّة يا لينا الع!
    switch (desirable_information) {
        case CITIZEN_ID:information = citizen->id;
        case CITIZEN_NAME:information = citizen->name;
        case CITIZEN_EDUCATION_YEARS:information = citizen->education_years;
        case CITIZEN_AGE:information = citizen->age;
    }
}
void CitizenCandidateToBeRemovePrefrences(Citizen citizen){
    uniqueOrderedListClear(citizen->prefrences);
}
Vote CitizenFindPrefernce(Citizen citizen,int candidate_id) {
    Vote vote = uniqueOrderedListGetLowest(citizen->prefrences);
    while (vote) {
        if (PreferenceGetId(vote) == candidate_id)
            return vote;
        vote = uniqueOrderedListGetNext(citizen->prefrences);
    }
    return vote;
}
void CitizenRemovePrefrence(Citizen citizen, int candidate_id) {
    Vote vote =CitizenFindPrefernce(citizen,candidate_id);
    uniqueOrderedListRemove(citizen->prefrences, vote);
}
/*Vote CitizenGetPrefrence(Citizen citizen,int candidate_id)
{lina 3m tjrb lmkledet bs wleshy kter w wow !!!!
 wow
 jd wow
gogo wq7...
    Vote preference=uniqueOrderedListGetLowest(citizen->prefrences);
    while(preference) {
        if(PreferenceGetId(preference)==candidate_id){
        }
    }
}*/
int CitizenGetid(Citizen citizen){
    return *(citizen->id);
}
//maybe no:

void CitizenChangeInformation(Citizen citizen,int id,const String name,int education_years,int age){
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
    Vote vote=PreferenceCreate();
    PreferenceChangeInformation(vote,candidate_id,priority);
    if(uniqueOrderedListInsert(citizen->prefrences,vote)==UNIQUE_ORDERED_LIST_ITEM_ALREADY_EXISTS)
        return false;
    return true;
}