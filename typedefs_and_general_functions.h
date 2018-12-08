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
    GENERAL_CITIZEN_ID,
    GENERAL_CITY_ID,
    GENERAL_CANDIDATE_ID,
    GENERAL_CITIZEN_PRIORITY
}mtmElectionsGeneralInput;
typedef struct  City_t* City;
typedef struct Citizen_t * Citizen;
typedef struct Candidate_t * Candidate;
typedef struct  Preference_t *  Preference;
typedef struct Vote_t *Vote;
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
#define NOT_FOUND -1
#define NO_VOTES 0
#define INT_NULL_ARGUMENT 0
#define VOTE 1
//String StringCopy(String);
void StringCopy(const String source_string,String destination);
size_t Stringlength( String );
int StringCompare(const char* s1, const char* s2);
#endif //UNTITLED1_TYPEDEFS_H