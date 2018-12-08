//
// Created by George on 12/7/2018.
//

#include "Vote.h"
#include <stdio.h>
struct Vote_t{
  int candidate_id;
  Name candidate_name;
  int candidate_votes;
  EducationYears candidate_education_years;
  Age candidate_age;
};
Vote VoteCreate() {
    Vote vote=(Vote)malloc(sizeof(*vote));
    if(vote==NULL)
        return NULL;
    vote->candidate_id=(Id)malloc(sizeof(*vote->candidate_id));
    vote->candidate_age=(Age)malloc(sizeof(*vote->candidate_age));
    vote->candidate_education_years=(EducationYears)
            malloc(sizeof(*vote->candidate_education_years));
   // vote->candidate_name=(String)malloc(sizeof(String*)*
      //
      //     Stringlength(vote->candidate_name));
    return vote;
}

Vote  VoteCopy(Vote vote){
    Vote vote_copy=VoteCreate();
    if(vote_copy->candidate_name==NULL ||vote_copy->candidate_id==NULL ||
            vote_copy->candidate_age==NULL ||vote_copy->candidate_education_years==NULL)
        VoteDestroy(vote_copy);
    return vote_copy;
}
void VoteDestroy(Vote vote){
    if(vote==NULL)
        return;
    free((vote->candidate_education_years));
    free(vote->candidate_age);
    free(vote->candidate_id);
    free(vote->candidate_name);
}
bool VoteIsEqual(Vote vote_old,Vote vote_new){
    return *(vote_new->candidate_id)==*(vote_old->candidate_id);
}
bool VoteGreaterThan(Vote vote_old,Vote vote_new){
    if((vote_old->candidate_votes)<(vote_new->candidate_votes))
        return true;
    if((vote_old->candidate_votes)>(vote_new->candidate_votes))
        return false;
    if(StringCompare(vote_new->candidate_name,vote_old->candidate_name)<0)
        return true;
    if(StringCompare(vote_old->candidate_name,vote_new->candidate_name)<0)
        return false;
    if(*(vote_old->candidate_id)<*(vote_new->candidate_id))
        return true;
    return (*(vote_old->candidate_id)>=*(vote_new->candidate_id));
}
bool VoteElectionsGreaterThan(Vote vote_old,Vote vote_new){

    if(StringCompare(vote_new->candidate_name,vote_old->candidate_name)<0)
        return true;
    if(StringCompare(vote_old->candidate_name,vote_new->candidate_name)<0)
        return false;
    if(*(vote_old->candidate_id)<*(vote_new->candidate_id))
        return true;
    return (*(vote_old->candidate_id)>=*(vote_new->candidate_id));
}
void VoteInsertInformation(Vote vote,int candidate_id, Name candidate_name, int
candidate_votes, int candidate_education_years, int candidate_age){
    *vote->candidate_id=candidate_id;
    vote->candidate_votes=candidate_votes;
    *vote->candidate_education_years=candidate_education_years;
    *vote->candidate_age=candidate_age;
    vote->candidate_name=
            (String)malloc(sizeof(String*)*Stringlength(candidate_name));
    StringCopy(candidate_name,vote->candidate_name);
}
int VoteCandidateGetId(Vote vote){
    return *(vote->candidate_id);
}
int VoteCandidateGetVotes(Vote vote){
    if(vote==DOES_NOT_EXIST)return NO_VOTES;
    return vote->candidate_votes;
}
void VotePrint(Vote vote){
    printf("==============================\n");
    printf("Vote for:%d\n",*vote->candidate_id);
    printf("Votes so far:%d\n",vote->candidate_votes);

    printf("==============================\n");
}