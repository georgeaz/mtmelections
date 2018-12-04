//
// Created by User on 30/11/2018.
//

#ifndef UNTITLED1_TYPEDEFS_H
#define UNTITLED1_TYPEDEFS_H
#include <stddef.h>
#include <stdlib.h>

typedef enum mtmElectionsGeneralInput_t{
    GENERAL_ID,
    GENERAL_AGE,
    GENERAL_EDUCATION_YEARS,
    GENERAL_
}mtmElectionsGeneralInput;
typedef struct  City_t* City;
typedef struct Citizen_t * Citizen;
typedef struct Candidate_t * Candidate;
typedef struct  Preference_t *  Vote;
typedef int* Id;
typedef int* Age;
typedef char* String;
typedef char * Name;
typedef void* Information;
typedef int* EducationYears;
typedef int Priority;
#define CANDIDATE_MINIMUM_AGE 21
#define VOTER_MINIMUM_AGE 17
#define FIRST_CITIZEN_LEGAL_ID 0
#define FIRST_CITY_LEGAL_ID 0
#define LAST_BIT 1
#define DOES_NOT_EXIST NULL

//String StringCopy(String);
void StringCopy(const String source_string,String destination);
size_t Stringlength( String );
#endif //UNTITLED1_TYPEDEFS_H