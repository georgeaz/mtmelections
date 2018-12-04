//
// Created by George on 12/1/2018.
//
#include "Candidate.h"
#include "stdlib.h"

 struct Candidate_t{
  Id id;
};
Candidate CandidateCreate(){
    Candidate candidate=(Candidate)malloc(sizeof(*candidate));
    if(candidate==NULL)
        return NULL;
    Id id=(Id)malloc(sizeof(*id));
    if(id==NULL){
        CandidateDestroy(candidate);
        return NULL;
    }
    candidate->id=id;
    return candidate;
}
void CandidateDestroy(Candidate candidate){
    free(candidate->id);
    free(candidate);
}
void CandidateChangeId(Candidate candidate,int id){
    *(candidate->id)=id;
}
Candidate CandidateCopy(Candidate source_candidate){
    Candidate new_candidate=(Candidate)malloc(sizeof(*new_candidate));
    if(source_candidate==NULL)return NULL;
    if(new_candidate==NULL)return NULL;
    new_candidate->id=source_candidate->id;
    return new_candidate;
}
bool CandidateCompare(Candidate candidate_new,Candidate candidate_old){
    return candidate_new->id==candidate_old->id;
}
int CandidateGetId(Candidate candidate){
    return *(candidate->id);
}