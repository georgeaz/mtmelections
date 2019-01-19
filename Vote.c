//
// Created by George on 12/7/2018.
//

#include "Vote.h"
#include <stdio.h>
struct Vote_t{
  Id candidate_id;
  Name candidate_name;
  int* candidate_votes;
};
Vote VoteCreate() {
    Vote vote=(Vote)malloc(sizeof(*vote));
    Id candidate_id=(Id)malloc(sizeof(*candidate_id));
    int* candidate_votes=(int*)malloc(sizeof(*candidate_votes));
    if(vote==NULL||candidate_id==NULL||candidate_votes==NULL)
        return NULL;
        vote->candidate_id=candidate_id;
    vote->candidate_votes=candidate_votes;
    return vote;
}

Vote  VoteCopy(Vote source_vote){
    Vote vote_copy=VoteCreate();
    if(source_vote==NULL||vote_copy==NULL)
        return NULL;
    vote_copy->candidate_name=(String)malloc(sizeof(String*)*Stringlength(source_vote->candidate_name));
    if(vote_copy->candidate_name==NULL) {
        VoteDestroy(vote_copy);
        return NULL;
    }
    StringCopy(source_vote->candidate_name,vote_copy->candidate_name);
    *(vote_copy->candidate_votes)=*(source_vote->candidate_votes);
    *(vote_copy->candidate_id)=*(source_vote->candidate_id);
    return vote_copy;
}
void VoteDestroy(Vote vote){
    if(vote==NULL)
        return;
    free((vote->candidate_id));
    free(vote->candidate_votes);
    free(vote->candidate_name);
    free(vote);
}
bool VoteIsEqual(Vote vote_old,Vote vote_new){
    return *(vote_new->candidate_id)==*(vote_old->candidate_id);
}
bool VoteGreaterThan(Vote vote_old,Vote vote_new){
    if(*(vote_old->candidate_votes)<*(vote_new->candidate_votes))
        return true;
    if(*(vote_old->candidate_votes)>*(vote_new->candidate_votes))
        return false;
    if(StringCompare(vote_new->candidate_name,vote_old->candidate_name)>0)
        return  false ;
    if(StringCompare(vote_old->candidate_name,vote_new->candidate_name)>0)
        return true;
    if(*(vote_old->candidate_id)<*(vote_new->candidate_id))
        return true;
    return (*(vote_old->candidate_id)>=*(vote_new->candidate_id));
    //return true ;
}
bool VoteElectionsGreaterThan(Vote vote_old,Vote vote_new){
    if(StringCompare(vote_new->candidate_name,vote_old->candidate_name)>0)
        return  false ;
    if(StringCompare(vote_old->candidate_name,vote_new->candidate_name)>0)
        return true;

    if (*(vote_old->candidate_id)>*(vote_new->candidate_id))
        return true;
    return (*(vote_old->candidate_id)<*(vote_new->candidate_id));
        return true;
}
void VoteInsertInformation(Vote vote,int candidate_id, Name candidate_name, int
candidate_votes){
    *(vote->candidate_id)=candidate_id;
    *(vote->candidate_votes)=candidate_votes;
    vote->candidate_name=
            (String)malloc(sizeof(String*)*Stringlength(candidate_name));
    StringCopy(candidate_name,vote->candidate_name);
}
int VoteCandidateGetId(Vote vote){
    return *(vote->candidate_id);
}
int VoteCandidateGetVotes(Vote vote){
    if(vote==DOES_NOT_EXIST)return NO_VOTES;
    return *(vote->candidate_votes);
}
