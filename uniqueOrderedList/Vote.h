//
// Created by George on 12/7/2018.
//

#ifndef INC_3011_VOTE_H
#define INC_3011_VOTE_H
#include <stdbool.h>
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

Vote VoteCreate();
void VoteInsertInformation(Vote vote,int candidate_id, Name candidate_name, int
candidate_votes, int candidate_education_years, int candidate_age);
Vote  VoteCopy(Vote vote);
void VoteDestroy(Vote vote);
bool VoteIsEqual(Vote vote_old,Vote vote_new);
bool VoteGreaterThan(Vote vote_old,Vote vote_new);
int VoteCandidateGetId(Vote vote);
int VoteCandidateGetVotes(Vote vote);
bool VoteElectionsGreaterThan(Vote ,Vote );
void VotePrint(Vote vote);
#endif //INC_3011_VOTE_H
